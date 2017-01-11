#version 330

layout(location=0) in vec2 vertexPosition;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec2 vertexUV;

uniform mat4 P;
uniform vec2 offsetVec;

out vec2 fragmentUV;
out vec4 fragmentColor;

void main() {
    gl_Position.xy = (P * vec4(vertexPosition + offsetVec, 0.0, 1.0)).xy;
    gl_Position.w = 1.0;
    gl_Position.z = 0.0;
    vec2 bacOffset = offsetVec; 
    fragmentUV = vertexUV;
    fragmentColor = vertexColor;
    
    
}
