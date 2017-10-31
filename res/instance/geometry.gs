#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;
in VS_OUT{
	vec2 texcoord;
	vec3 normal;
	vec3 fragPos;
} gs_in[];
out VS_OUT{
	vec2 texcoord;
	vec3 normal;
	vec3 fragPos;
} gs_out;
vec3 GetNormal();
vec4 explode(vec4 position, vec3 normal);

void main(){
	vec3 normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	gs_out.texcoord = gs_in[0].texcoord;
	gs_out.normal = gs_in[0].normal;
	gs_out.fragPos = gs_in[0].fragPos;
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
	gs_out.texcoord = gs_in[1].texcoord;
	gs_out.normal = gs_in[1].normal;
	gs_out.fragPos = gs_in[1].fragPos;
	EmitVertex();
	gl_Position = explode(gl_in[2].gl_Position, normal);
	gs_out.texcoord = gs_in[2].texcoord;
	gs_out.normal = gs_in[2].normal;
	gs_out.fragPos = gs_in[2].fragPos;
	EmitVertex();
	EndPrimitive();
}
vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}
vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * (0.1) * magnitude; 
    return position + vec4(direction, 0.0);
}