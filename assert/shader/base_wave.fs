#version 330 core
#ifdef GL_ES
precision mediump float;
#endif
out vec4 FragColor;
in vec2 TexCoord;
in float vTexIndex;

uniform sampler2D ourTexture;
uniform float uTime; //默认的时间，动态改变


void main()
{
    vec2 vUv = TexCoord.xy;

    // 振幅（控制波浪顶端和底端的高度）
    float amplitude = 0.35;

    // 角速度（控制波浪的周期）
    float angularVelocity = 10.0;

    // 频率（控制波浪移动的速度）
    float frequency = 5.0;

    // 偏距（波浪垂直偏移量）
    float offset = 0.0;

    // 初相位（正值表现为向左移动，负值则表现为向右移动）
    float initialPhase = frequency * uTime;

    // 代入正弦曲线公式计算 y 值
    // y = Asin(ωx ± φt) + k
    float y = amplitude * sin((angularVelocity * vUv.x) + initialPhase) + offset;

    vUv.y += y / 20.0;

    FragColor = texture(ourTexture, vUv);
}