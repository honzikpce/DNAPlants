#version 330

//in vec2 fragmentPosition;
in vec4 fragmentColor;
//in vec2 fragmentUV;

out vec4 color;

//uniform sampler2D mySampler;

void main(void) {
    
    
    
    //vec4 textureColor = texture(mySampler, fragmentUV);
    //vec4 bac = fragmentColor;
    color = fragmentColor;
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

}
