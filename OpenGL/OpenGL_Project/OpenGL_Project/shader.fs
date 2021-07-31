#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform vec2 cursorXY;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    vec2 uv = TexCoord;
    vec2 screenCoords = (uv + 0.5) * 0.5;
    
    vec2 cursorUV = vec2(clamp(cursorXY.x, 0.0, 1.0), clamp(1.0 - cursorXY.y, 0.0, 1.0));
    
    float alpha = max(0.0, 1.3 - (length(vec2(screenCoords.x - cursorUV.x, screenCoords.y - cursorUV.y))));
    alpha *= alpha;
    
    
    FragColor = mix(texture(texture1, uv), texture(texture2, vec2(uv.x, uv.y)), 0.2);
    FragColor *= alpha;
}
