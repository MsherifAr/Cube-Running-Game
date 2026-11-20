#version 330 core

out vec4 FragColor;

in vec2 texCord;
uniform sampler2D UI_texture;
uniform float transparency;

void main(){
	vec4 texColor = texture(UI_texture, texCord);
	if (texColor.a < 0.1) {
        discard;
    }
	FragColor = texColor * vec4(transparency);
}