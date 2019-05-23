#version 410

layout (location=0) in vec2 aPos;

//uniform float screenRatio;
uniform vec2 move;
uniform mat4 projection;

void main(){
    gl_Position=vec4(aPos+move,0.0,1.0);//add projection
}