#version 330

in vec2 fragmentUV;
in vec4 fragmentColor;
uniform bool isTextureBound;

out vec4 color;

uniform sampler2D mySampler;

void main(void) {
    
    


    if (isTextureBound) {

    vec4 textureColor = texture(mySampler, fragmentUV);
    color = textureColor * fragmentColor;
    }
    else  {
        color = fragmentColor;
    }

    //textureColor.a = 1.0f;
    //color = vec4(fragmentUV.y, 0.0f,  0.0f, 1.0f);


}
