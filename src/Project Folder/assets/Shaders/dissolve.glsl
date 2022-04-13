#ifdef vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    texCoords = TexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}  
#endif

#ifdef fragment
#version 330 core
precision mediump float;

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;
in vec2 texCoords;

//uniform vec3 cameraPos;
uniform float time;
uniform vec3 lightDir;
uniform sampler2D mainTexture;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = smoothstep(0.,1.,f);
    return mix(a, b, u.x) + (c - a)* u.y * (1.0 - u.x) +(d - b) * u.x * u.y;
}


void main()
{             
    vec2 st = texCoords;
    float timeIter = sin(time);

    if(st.x >= 0.5)
    {
        st.x = 1.0-st.x;
    }
        if(st.y >= 0.5)
    {
        st.y = 1.0-st.y;
    }

    vec2 pos = vec2(st*20.5);

    float n = noise(pos);
	for(int i = 0; i < 2; i++)
    {
    	n = noise(vec2(n, n));
    }

    vec3 finalColor = vec3(1.0, 0.6, 0.1);
    vec3 midColor = vec3(1.0, 0.0, 0.0);

    float finalAlpha = 1.0-((1.0-n)-timeIter);
    for(float i = 0.0; i <= 1.0; i+= 0.25){
        if(finalAlpha <= i){
            finalColor = mix(midColor, finalColor, i);
            break;
        }
    }

    float intensity = dot(lightDir, Normal);


    if (intensity > 0.4)
		finalColor *= 1.0;
	else if(intensity > 0.1)
		finalColor *= 0.5;
    else
		finalColor *= 0.20;

    FragColor = vec4(finalColor, finalAlpha) * texture(mainTexture, texCoords);
}
#endif

