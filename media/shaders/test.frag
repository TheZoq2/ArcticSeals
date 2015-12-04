#version 130
const int MAX_LIGHTS = 64;

uniform sampler2D texture;
uniform sampler2D normalTexture;

uniform int lightAmount = 0;
uniform float lightRanges[64];
uniform vec4 lightColors[64];
uniform vec4 lightPositions[64];

varying vec4 vertexPos;

//vec4 lightPos = vec4(0,0,3,0);
//vec4 lightColor = vec4(255.0/255.0, 180.0/255.0, 51.0/255.0, 0.7);
//vec4 lightColor = vec4(255.0/255.0, 255.0/255.0, 200.0/255.0, 0.7);

vec4 ambientLight = vec4(0.1,0.1,0.1, 1.0);

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    vec4 finalLight = vec4(0,0,0, 0);


    for(int i = 0; i < lightAmount; ++i)
    {
        vec4 lightPos = lightPositions[i];
        vec4 lightColor = lightColors[i];
        //float lightRange = lightRanges[i];
        float lightRange = 0;
        
        //Calculating the light influence
        vec4 lightToPoint = vertexPos - lightPos;
        vec4 normalLightToPoint = normalize(lightToPoint);
        float lightAmount = pow(dot(normalLightToPoint, texture2D(normalTexture, gl_TexCoord[0].xy)),5);

        float lightRangeMod = 1.0 - length(lightToPoint) / lightRange;
        clamp(lightRangeMod, 0, 1);

        lightAmount *= lightRangeMod;

        finalLight += lightAmount * lightColor;
    }

    // multiply it by the color
    gl_FragColor = gl_Color * pixel * ambientLight + pixel * finalLight;
    //gl_FragColor = gl_Color * pixel * lightAmount;
    //gl_FragColor = gl_Color * lightColor * lightAmount;
    gl_FragColor.a = pixel.a;
    //gl_FragColor = vec4(1,0,0,1);
}
