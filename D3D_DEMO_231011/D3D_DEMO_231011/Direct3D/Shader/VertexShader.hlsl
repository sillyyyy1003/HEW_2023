// ���_�V�F�[�_�[

// ���_�̃f�[�^��\���\���́i�󂯎��p�j
struct VS_IN
{
        float4 pos : POSITION0; // �ʒu���W������
        float2 tex : TEX;       // UV���W������
};

// ���_�̃f�[�^��\���\���́i���M�p�j 
struct VS_OUT
{
        float4 pos : SV_POSITION;
        float2 tex : TEXCOORD;
};

// �O���[�o���ϐ��̐錾
// �萔�o�b�t�@�󂯎��p
cbuffer ConstBuffer : register(b0)
{
    // UV���W�ړ��s��
    matrix matrixTex;
    // ���e�s��
    matrix matrixProj;
    // ���[���h�ϊ��s��
    matrix matrixWorld;
}
 

// ���_�V�F�[�_�[�̃G���g���|�C���g 
VS_OUT vs_main( VS_IN input )
{
    VS_OUT output;
 
    // ���[���h�ϊ��s��𒸓_�Ɋ|����
    input.pos = mul(input.pos, matrixWorld);
    
    // ���s���e�̂��ߍs��𒸓_�Ɋ|����
    output.pos = mul(input.pos, matrixProj);
    
    // UV���W���ړ�������
    float4 uv;
    uv.xy = input.tex; // �s��|���Z�̂���float4�^�Ɉڂ�
    uv.z = 0.0f;
    uv.w = 1.0f;
    uv = mul(uv, matrixTex); // UV���W�ƈړ��s����|���Z
    
    output.tex = uv.xy; // �|���Z�̌��ʂ𑗐M�p�ϐ��ɃZ�b�g
    
    return output;
}