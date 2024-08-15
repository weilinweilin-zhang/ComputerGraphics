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
    // 在顶点着色器里面通过坐标计算，在这里来的，中间都经过光栅化做一层加权平均数，然后在片段后获取真实的平均数
    // 纹理 顶点坐标 法向量也是 也进行加权的。
    // 获取纹理坐标
    vec3 ambient =light.ambient * texture(material.diffuse,TexCoords).rgb;
    // 法向量 在顶点着色器里面传进来
    vec3 norm = normalize(Normal);
    // 光的向量 与fragPos的法向量
    vec3 lightDir = normalize(light.position - FragPos);
    // 防止负数 ,负数的话就是超过90°的片段就会 负数的分量，把原本的环境直接干掉
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;

    // 反射
    // 视角的角度
    vec3 viewDir = normalize(viewPos - FragPos);
    // 反射的角度
    vec3 reflectDir = reflect(-lightDir,norm);
    // 然后向量点乘 ，小于90°的显示出来, 然后幂指数乘上 聚光的程度，shininess越强，越聚光，反之散光
    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    // 然后乘上反射光的系数得到反射光的系数
    vec3 specular = light.specular * (spec* material.specular);
    // 在顶点着色的phong 就是顶点，在片段的着色器，就是一个片段一个面的计算插值啥的
    // 三种光线分别贡献加上去
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0f);
} 