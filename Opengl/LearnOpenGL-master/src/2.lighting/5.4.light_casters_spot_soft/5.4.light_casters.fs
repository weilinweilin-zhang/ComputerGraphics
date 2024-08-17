#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);   // 摄像机坐标  减去片段坐标
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;   //分量乘上反射的纹理数据
    // 反射就是 光的方向 和法向量计算 反射向量，然后 与摄像机视角 做点乘，然后乘上 shininess; 做散光 ，幂函数越大，变化频率也快
    

    // 这些都是算  光照程度的 ， 衰减也是
    // 光的方向 ，然后光到无敌的方向，
    float theta = dot(lightDir,normalize(-light.direction));
    // 内切和外切
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity =  clamp( (theta - light.cutOff) / epsilon,0,1);

    diffuse *= intensity;
    specular *= intensity;
    // 衰减是根据 距离来的，光的坐标在片段的坐标 ，二元一次方程计算 变化速率
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    // 将三种颜色进行混合
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 