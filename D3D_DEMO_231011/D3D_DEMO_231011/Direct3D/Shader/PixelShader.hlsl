// �s�N�Z���V�F�[�_�[

// �s�N�Z���̏��̍\���́i�󂯎��p�j
struct PS_IN
{
    // float4�^�@���@float�^���S�̍\����
    float4 pos : SV_POSITION; // �s�N�Z���̉�ʏ�̍��W
    float2 tex : TEXCOORD;  // �s�N�Z���ɑΉ�����e�N�X�`�����W
};

// �O���[�o���ϐ��̐錾
// ���V�F�[�_�[�̃O���[�o���ϐ��́AC����v���O��������n���ꂽ
// �@�f�[�^���󂯎�邽�߂Ɏg���B
Texture2D myTexture : register(t0); //�e�N�X�`���[
SamplerState mySampler : register(s0); //�T���v���[

// �s�N�Z���V�F�[�_�[�̃G���g���|�C���g
float4 ps_main(PS_IN input) : SV_Target
{
    // Sample�֐����e�N�X�`������w�肵��UV�����Ƀs�N�Z���F������ė���
    float4 color = myTexture.Sample(mySampler, input.tex);    
    return color;
}