#version 120

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float rampOn;
uniform float xCoord;
uniform float yCoord;
uniform float screenPropHorizontal;
uniform float screenPropVertical;

varying vec2 f_texcoord;
 
void main(void) {

	
	vec2 texcoord = f_texcoord;

	if (rampOn > 0.5) {

		if (texcoord.x <= xCoord/800.0 + screenPropHorizontal && texcoord.x >= xCoord/800.0 - screenPropHorizontal
		 && texcoord.y <= yCoord/600.0 + screenPropVertical && texcoord.y >= yCoord/600.0 - screenPropVertical) {
			vec3 inColor = texture2D(texture1, texcoord).xyz;
			vec3 outColor;

			outColor.r = texture2D(texture2, vec2(inColor.r, 1)).r;
			outColor.g = texture2D(texture2, vec2(inColor.g, 1)).g;
			outColor.b = texture2D(texture2, vec2(inColor.b, 1)).b;

			gl_FragColor = vec4(outColor, 1.0);
		} else {
			gl_FragColor = texture2D(texture1, texcoord);
		}
	} else {
		gl_FragColor = texture2D(texture1, texcoord);
	}
}