#version 330 core

out vec4 oFragColor;

struct SMaterial {
    sampler2D _Diffuse;
    sampler2D _Specular;    
    float _Shininess;
}; 

struct SDirLight {
    vec3 _Direction;
    vec3 _Ambient;
    vec3 _Diffuse;
    vec3 _Specular;
};

in vec3 vFragPos;  
in vec3 vNormal;  
in vec2 vTexCoords;
in vec4 vFragPosLightSpace;
  
uniform vec3 uViewPos;
uniform SMaterial uMaterial;
uniform SDirLight uLight;
uniform bool uReceiveShadow;
uniform sampler2D uShadowMap;


vec3 calcBlinnPhong(float Shadow)
{
    // Ambient
    vec3 Ambient = uLight._Ambient * texture(uMaterial._Diffuse, vTexCoords).rgb;
  	
    // Diffuse 
    vec3 Normal = normalize(vNormal);
    vec3 LightDir = normalize(-uLight._Direction);
    float Diff = max(dot(Normal, LightDir), 0.0);
    vec3 Diffuse = uLight._Diffuse * Diff * texture(uMaterial._Diffuse, vTexCoords).rgb;  
    
    // Specular
    vec3 ViewDir = normalize(uViewPos - vFragPos);
    vec3 ReflectDir = reflect(-LightDir, Normal);  
    float Spec = pow(max(dot(ViewDir, ReflectDir), 0.0), uMaterial._Shininess);
    vec3 Specular = uLight._Specular * Spec * texture(uMaterial._Specular, vTexCoords).rgb;
        
    return Ambient + (Diffuse + Specular) * (1.0 - Shadow);
}

float calcBias()
{
    vec3 Normal = normalize(vNormal);
    vec3 LightDir = normalize(-uLight._Direction);
    float Bias = max(0.05 * (1.0 - dot(Normal, LightDir)), 0.005);
    Bias = 0.0001;
    return Bias;
}

float calcShadow()
{
    vec3 ProjCoords = vFragPosLightSpace.xyz / vFragPosLightSpace.w;
    ProjCoords = ProjCoords * 0.5 + 0.5;
    float ClosestDepth = texture(uShadowMap, ProjCoords.xy).r; 
    float CurrentDepth = ProjCoords.z;

    float Bias = calcBias();
    float Shadow = CurrentDepth - Bias > ClosestDepth  ? 1.0 : 0.0;

    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(ProjCoords.z > 1.0)
        Shadow = 0.0;
        
    return Shadow;
}

void main()
{
    float Shadow = uReceiveShadow ? calcShadow() : 0.0;
    Shadow = min(Shadow, 0.75);
    oFragColor = vec4(calcBlinnPhong(Shadow), 1.0);
} 