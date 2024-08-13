#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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
    float diff = dot(norm, lightDir);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);

    // 在顶点着色器里面通过坐标计算，在这里来的，中间都经过光栅化做一层加权平均数，然后在片段后获取真实的平均数
    // 纹理 顶点坐标 法向量也是 也进行加权的。
    // 获取纹理坐标
    //vec3 ambient =light.ambient * texture(material.diffuse,TexCoords).rgb;
    // 法向量 在顶点着色器里面传进来
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    // 防止负数
    //float diff = max(dot(norm,lightDir),0.0);

} 