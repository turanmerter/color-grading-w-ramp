#version 120

uniform sampler2D texture1;
uniform sampler2D texture2;

varying vec2 f_texcoord;
 
void main(void) {
    //vec2 texcoord = f_texcoord;
    //gl_FragColor = texture2D(texture1, texcoord) + texture2D(texture2, texcoord);


	vec2 texcoord = f_texcoord;

	vec3 inColor = texture2D(texture1, texcoord).xyz;
	vec3 outColor;

	outColor.r = texture2D(texture2, vec2(inColor.r, 1)).r;
	outColor.g = texture2D(texture2, vec2(inColor.g, 1)).g;
	outColor.b = texture2D(texture2, vec2(inColor.b, 1)).b;

    gl_FragColor = vec4(outColor, 1.0);
}

