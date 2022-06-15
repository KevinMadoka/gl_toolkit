#version 410 core
out vec4 FragColor;
void main()
{
   float lerpValue = gl_FragCoord.y / 480.0f;
   FragColor = mix(vec4(1.0f, 0.5f, 0.2f, 1.0f), vec4(0.2f, 0.2f, 0.2f, 0.2f), lerpValue);
}

