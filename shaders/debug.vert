#version 330

layout(location=0) in vec2 vertexPosition;
layout(location=1) in vec4 vertexColor;
//layout(location=2) in vec2 vertexUV;

uniform mat4 P;

out vec4 fragmentColor;
//out vec2 fragmentPosition;
//out vec2 fragmentUV;

void main() {
    //mat4 id = mat4(0.0);
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    //gl_Position.xy = (id * vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position.w = 1.0;
    gl_Position.z = 0.0;
    
    //mat4 bacProjection = P;
    fragmentColor = vertexColor;
    //fragmentPosition = vertexPosition;
    //fragmentUV = vec2(vertexUV.x, 1 - vertexUV.y);
    
    
    
}
