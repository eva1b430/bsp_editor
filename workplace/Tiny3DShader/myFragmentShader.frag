varying vec4 v_fragmentColor; 
uniform sampler2D CC_Texture0;

varying vec2 v_coord;
varying vec3 v_normal;
 
uniform vec4 u_color;

void main()
{    
	//gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_coord) * u_color;
	gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_coord);
	//gl_FragColor = texture2D(CC_Texture0, v_coord);
}