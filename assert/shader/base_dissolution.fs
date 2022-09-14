#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in float vTexIndex;
in vec3 vLocalCoord;

uniform sampler2D ourTexture;
uniform float uTime; //默认的时间，动态改变
uniform float burn_value;
uniform sampler2D noiseTexture;
uniform vec3 burn_color;

void main()
{

    vec2 vUv = TexCoord.xy;

    // 振幅（控制波浪顶端和底端的高度）
    float amplitude = 0.85;

    // 角速度（控制波浪的周期）
    float angularVelocity = 10.0;

    // 频率（控制波浪移动的速度）
    float frequency = 1.0;

    // 偏距（波浪垂直偏移量）
    float offset = 0.0;

    // 初相位（正值表现为向左移动，负值则表现为向右移动）
    float initialPhase = frequency * uTime;

    // 代入正弦曲线公式计算 y 值
    // y = Asin(ωx ± φt) + k
    float y = amplitude * sin((angularVelocity * vUv.x) + initialPhase) + offset;

    vUv.y += y / 20.0;


    float noise = texture(noiseTexture, vUv).r + 0.25;
    noise += + 0.5;
    float burn =  noise * burn_value;
    float height = vLocalCoord.y + 0.6 ;
    if(height - burn < 0.0){
        discard;
    }
    float width = 0.03;
    float gap = height  - burn - width;

    if(gap < 0){
         FragColor = texture(ourTexture, vUv) *  vec4(burn_color,1.0) ;
    }else{
        FragColor = texture(ourTexture, TexCoord.xy);
    }

}