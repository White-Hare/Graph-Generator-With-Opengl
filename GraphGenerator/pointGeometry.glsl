#version 410

layout(points) in;

layout(triangle_strip,max_vertices=4) out;

uniform mat4 projection;

void main(){
    

    gl_Position=gl_in[0].gl_Position+vec4(-0.01,-0.01,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(0.01,-0.01,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(-0.01,0.01,0.0,0.0);
    EmitVertex();

    gl_Position=gl_in[0].gl_Position+vec4(0.01,0.01,0.0,0.0);
    EmitVertex();

    EndPrimitive();

}