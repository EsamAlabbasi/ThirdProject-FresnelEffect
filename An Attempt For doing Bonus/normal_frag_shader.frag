#version 120

// vertex shaderindan gelen veriler
varying vec3 camera_normal_product;

uniform float R0;
uniform float R1;

// fragment shader main metodu
void main(void)
{

	vec3 product = normalize(camera_normal_product);
	vec3 GREEN = vec3( 0.0, 0.8, 0.0 );
	vec3 BROWN = vec3( 0.6, 0.3, 0.1 ); 
	vec3 z_Position = vec3( 0.0, 0.0, -1.0 );
	float angle = dot(product, z_Position);
	float cosResult = cos(angle);
	cosResult = R0 + ((1-R0)*pow((1+angle), R1));
	vec3 fresnelEffect = vec3(mix(GREEN, BROWN,cosResult));
	// gl_FragColor ekrana basilacak rengi secer
	gl_FragColor = vec4(normalize(fresnelEffect),1.0);
}
