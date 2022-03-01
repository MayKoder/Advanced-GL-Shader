#ifdef vertex
#version 330 core

layout (location = 0) in vec3 pointPositions;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 position;
uniform mat3 normalMatrix;

out vec3 FragPos;

out VS_OUT {
	mat4 MVP;
} vs_out;

void main()
{
	FragPos = vec3(position * vec4(pointPositions, 1.0f));
	vs_out.MVP = projection * view * position;
	gl_Position = projection * view * position * vec4(pointPositions, 1.0f);
}
#endif

#ifdef geometry
#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    mat4 MVP;
} gs_in[]; 

void build_house(vec4 position)
{    
    gl_Position = position + (gs_in[0].MVP * vec4( 0.007, 0.0, 0.0, 0.0));    // 2:bottom-right
    EmitVertex();
    gl_Position = position + (gs_in[0].MVP * vec4(-0.007, 0.0, 0.0, 0.0));    // 1:bottom-left
    EmitVertex();   
    gl_Position = position + (gs_in[0].MVP * vec4( 0.0,  0.05, 0.0, 0.0));    // 5:top
    EmitVertex();
    EndPrimitive();
}

void main() {    
    build_house(gl_in[0].gl_Position);
}  
#endif

#ifdef fragment
#version 330 core

uniform vec4 color;
uniform vec3 viewPos; 

in vec3 FragPos;

out vec4 FragColor;


void main()
{

	FragColor = vec4(0.203, 0.549, 0.192, 1.0);
}
#endif

