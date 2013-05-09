#version 120

// sabit degiskenler
uniform mat4 MVP;

// diziden alinacak degiskenler
attribute vec4 Position;
attribute vec3 Normal;

// fragment shader'a aktarilacak veriler
varying vec3 camera_normal_product;

// vertex shader main metodu
void main()
{
    // gl_Position ekranda noktanin nerede olacagini belirtir.
    gl_Position = MVP * Position;
    camera_normal_product = mat3(gl_ModelViewMatrix)*Normal;
	

}