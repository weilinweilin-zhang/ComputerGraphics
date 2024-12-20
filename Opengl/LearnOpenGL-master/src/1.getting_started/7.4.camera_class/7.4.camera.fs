#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
//	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//if(gl_FragCoord.x < 400)
     //   FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    //else
     //   FragColor = vec4(0.0, 1.0, 0.0, 1.0);   

	if(gl_FrontFacing)
        FragColor = texture(texture1, TexCoord);
    else
        FragColor = texture(texture2, TexCoord);
}