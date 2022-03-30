#ifdef vertex
#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 TexCoords;
layout (location = 2) in vec3 VertexNormal;

//uniform mat4 view;
//uniform mat4 projection;
//uniform mat4 position;
//uniform mat3 normalMatrix;
uniform mat4 transform;

out vec3 v_norm;
out vec4 v_pos; 

out VS_OUT {
    vec2 texCoords;
} vs_out;

void main()
{
	v_norm = VertexNormal;
	v_pos = vec4(VertexPosition, 1.0);

	vs_out.texCoords = TexCoords;
	//gl_Position = projection * view * position * vec4(VertexPosition, 1.0);
	gl_Position = transform * vec4(VertexPosition, 1.0);
}
#endif



#ifdef geometry
#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 
uniform float time;

vec4 explode(vec4 position, vec3 normal)
{
//Amout of explosion
    float magnitude =0.2;
	//Direction of explosion, going along normal
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
	//Returning position
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
//Getting the normal vector of each vertex
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   //returns the cross product between the two vectors calculated
   return normalize(cross(a, b));
}

void main()
{
//Getting normal
    vec3 normal = GetNormal();
//Setting current vertex position
    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();
    EndPrimitive();
}  
#endif



#ifdef fragment
#version 400

//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;
//Unfrom variable
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;

uniform sampler2D mainTexture;

//Passing out texture coordinates
in vec2 TexCoords; 
 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	vec4 color;
	color = vec4(randColourX,randColourY,randColourZ,1.0);
    fragcolor = texture(mainTexture, TexCoords) * color;
}
#endif

