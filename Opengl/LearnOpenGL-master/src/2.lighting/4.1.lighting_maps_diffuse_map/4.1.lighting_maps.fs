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
    // �ڶ�����ɫ������ͨ��������㣬���������ģ��м䶼������դ����һ���Ȩƽ������Ȼ����Ƭ�κ��ȡ��ʵ��ƽ����
    // ���� �������� ������Ҳ�� Ҳ���м�Ȩ�ġ�
    // ��ȡ��������
    vec3 ambient =light.ambient * texture(material.diffuse,TexCoords).rgb;
    // ������ �ڶ�����ɫ�����洫����
    vec3 norm = normalize(Normal);
    // ������� ��fragPos�ķ�����
    vec3 lightDir = normalize(light.position - FragPos);
    // ��ֹ���� ,�����Ļ����ǳ���90���Ƭ�ξͻ� �����ķ�������ԭ���Ļ���ֱ�Ӹɵ�
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse,TexCoords).rgb;

    // ����
    // �ӽǵĽǶ�
    vec3 viewDir = normalize(viewPos - FragPos);
    // ����ĽǶ�
    vec3 reflectDir = reflect(-lightDir,norm);
    // Ȼ��������� ��С��90�����ʾ����, Ȼ����ָ������ �۹�ĳ̶ȣ�shininessԽǿ��Խ�۹⣬��֮ɢ��
    float spec = pow(max(dot(viewDir,reflectDir),0.0), material.shininess);
    // Ȼ����Ϸ�����ϵ���õ�������ϵ��
    vec3 specular = light.specular * (spec* material.specular);
    // �ڶ�����ɫ��phong ���Ƕ��㣬��Ƭ�ε���ɫ��������һ��Ƭ��һ����ļ����ֵɶ��
    // ���ֹ��߷ֱ��׼���ȥ
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0f);
} 