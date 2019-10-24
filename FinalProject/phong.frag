#version 130

//
// Phong fragment shader
//
// Contributor:  Wei Zeng
//

// INCOMING DATA
uniform vec4 light_source_color;
uniform vec4 ambient_light_color;

uniform float ka;
uniform float kd;
uniform float ks;
uniform float se;

uniform vec4 amc;
uniform vec4 dmc;
uniform vec4 smc;

// ADD VARIABLES HERE for all data being sent from your vertex shader
in vec3 le;
in vec3 ve;
in vec3 ne;

// OUTGOING DATA
out vec4 finalColor;

///
// Main function
///

void main()
{
    // REPLACE THIS CODE with your implementation of this shader

    vec3 N = normalize(ne); //Viwing direction
	vec3 L = normalize(le - ve);//Direction to light source
	vec3 R = normalize (reflect(L, N));//Direction of perfect mirror reflection
    vec3 V = normalize (ve);//Viewing direction

	vec4 ambi = amc * ka * ambient_light_color;//Light from no direction (due to scattering) 
	vec4 diff = dmc * kd * (dot(N, L));//Light from a certain direction 
	vec4 spec = smc * ks * pow(max(0.0, dot(V,R)), se);//Directional light which reflects off a surface in a particular direction 

    finalColor = ambi + (diff  + spec)* light_source_color;//Final light is the sum of these contributing types: I = A + D + S
}