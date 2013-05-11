#version 120

// vertex shaderindan gelen veriler
varying vec3 normal,pos;

// fragment shader main metodu
void main(void)
{
    vec3 lightDir = vec3(gl_LightSource[0].position.xyz - pos);
	vec3 eyeVec = -pos;
    
    vec4 final_color = gl_LightSource[0].ambient;
    
	vec3 N = normalize(normal);
	vec3 L = normalize(lightDir);
	
	float lambertTerm = dot(N,L);
    
    final_color += gl_LightSource[0].diffuse * lambertTerm;	
    
    // Specular Light
    if(lambertTerm > 0.0)
	{
      vec3 E = normalize(eyeVec);
		vec3 R = reflect(-L, N);
		float specular = pow( max(dot(R, E), 0.0), 32 );
		final_color += gl_LightSource[0].specular * specular;	
	}
    
	gl_FragColor = final_color;
    
    
}
