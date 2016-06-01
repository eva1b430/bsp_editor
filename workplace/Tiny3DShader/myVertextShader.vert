attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_coord;
attribute vec3 Normal;

varying vec4 v_fragmentColor;
varying vec2 v_coord;
varying vec3 v_normal;

uniform mat4 MVP;
void main()
{
	// CC_MVPMatrix是cocos2dx默认的
	gl_Position = MVP * vec4(a_position.xyz, 1);
	
	//v_fragmentColor = a_color;
	//v_coord = a_coord;
	//v_normal = Normal;

	v_fragmentColor = vec4(1.0f,1.0f,1.0f,1.0f);
	v_coord = a_coord;
}