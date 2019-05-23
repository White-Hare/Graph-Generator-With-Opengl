#version 410

layout (points) in;
layout (line_strip,max_vertices=5) out;

uniform float size;
uniform mat4 projection;

void main(){

    gl_Position=gl_in[0].gl_Position+vec4(size,0.0,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(-size,0.0,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(0.0,0.0,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(0.0,size,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(0.0,-size,0.0,0.0);
    EmitVertex();

    EndPrimitive();
}