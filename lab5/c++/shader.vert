//
// Vertex shader for the transformation assignment
//
// Created by Warren R. Carithers 2016/04/22.
//
// Contributor:  Wei Zeng
//

#version 130

// attribute:  vertex position
in vec4 vPosition;

// add other global shader variables to hold the
// parameters your application code is providing
uniform float projection;

uniform vec3 scale;
uniform vec3 rotation;
uniform vec3 translation;

uniform vec3 eye;
uniform vec3 lookat;
uniform vec3 upvector;

float left = -1.0, right = 1.0, top = 1.0, bottom = -1.0, near = 0.9, far = 4.5;



void main()
{
    // By default, no transformations are performed.
    gl_Position =  vPosition;

	mat4 projectionMatrix;

	if(projection == 0.0) {
	//Frustum mode
	//[2*n/r-l, 0, r+l/r-l, 0,
	// 0, 2*n/t-b, t+b/t-b, 0,
	// 0, 0, -(f+n)/f-n, (-2*f*n)/f-n,
	// 0, 0, -1, 0]

	   projectionMatrix = mat4((2 * near) / (right - left), 0, 0, 0,
	   0, (2 * near) / (top - bottom), 0, 0,
	   (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near), -1,
	   0, 0, (-2 * far * near) / (far - near), 0);
	}
	if(projection == 1.0) {
	//Ortho mode
	//[2/r-l, 0, 0, -(r+l)/(r-l),
	// 0, 2/t-b, 0, -(t+b)/t-b,
	// 0, 0, -2/f-n, -(f+n)/f-n,
	// 0, 0, 0, 1]

	   projectionMatrix = mat4(2 / (right - left), 0, 0, 0,
	   0, 2 / (top - bottom), 0, 0,
	   0, 0, -2 / (far - near), 0,
	   -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1);
	}

	mat4 viewMatrix;
	//camera transformation
	//[ux, uy, uz, -1*(u*eyepoint),
	// vx, vy, vz, -1*(v*eyepoint),
	// nx, ny, nz, -1*(n*eyepoint),
	// 0, 0, 0, 1]

	vec3 n = normalize(eye - lookat);
	vec3 u = normalize(cross(upvector, n));
	vec3 v = cross(n, u);
	viewMatrix = mat4(u.x, v.x, n.x, 0.0,
		u.y, v.y, n.y, 0.0,
		u.z, v.z, n.z, 0.0,
		-1.0 * dot(u, eye), -1.0 * dot(v, eye), -1.0 * dot(n, eye), 1.0);

	mat4 translationMatrix;
	translationMatrix = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		translation.x, translation.y, translation.z, 1.0);

	mat4 scaleMatrix;
	scaleMatrix = mat4(scale.x, 0.0, 0.0, 0.0,
		0.0, scale.y, 0.0, 0.0,
		0.0, 0.0, scale.z, 0.0,
		0.0, 0.0, 0.0, 1.0);

	mat4 rotationMatrix;
	vec3 angle = radians(rotation), cosV = cos(angle),sinV = sin(angle);
	mat4 xMatrix = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cosV.x, sinV.x, 0.0,
		0.0, -sinV.x, cosV.x, 0.0,
		0.0, 0.0, 0.0, 1.0);
	mat4 yMatrix = mat4(cosV.y, 0.0, -sinV.y, 0.0,
		0.0, 1.0, 0.0, 0.0,
		sinV.y, 0.0, cosV.y, 0.0,
		0.0, 0.0, 0.0, 1.0);
	mat4 zMatrix = mat4(cosV.z, sinV.z, 0.0, 0.0,
		-sinV.z, cosV.z, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	rotationMatrix = zMatrix * yMatrix * xMatrix;

	//Clip space = [projection] * [Camera] * [Model] * Object space
	gl_Position = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix * vPosition;
}
