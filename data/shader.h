#pragma once

// �V�X�e��
#include <system\direct3d11.h>

// Utils
#include <utils\process.h>

// �W�����C�u����
#include <string>
#include <vector>

// API
#include <D3DX10.h>
#include <D3DX11.h>

struct IShader
{
	ID3D11VertexShader * vs_ = nullptr;
	ID3D11GeometryShader * gs_ = nullptr;
	ID3D11PixelShader * ps_ = nullptr;
	ID3D11InputLayout * layout_ = nullptr;
	ID3D11Buffer * cbuffer_ = nullptr;
	void * cb_ = nullptr;
	int cb_size = 0;

public:
	void Rendering(void)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();
		
		d3d->context_->IASetInputLayout(this->layout_);

		d3d->context_->VSSetShader(this->vs_, nullptr, 0);
		d3d->context_->GSSetShader(this->gs_, nullptr, 0);
		d3d->context_->PSSetShader(this->ps_, nullptr, 0);
		
		d3d->context_->VSSetConstantBuffers(0, 1, &this->cbuffer_);
		d3d->context_->GSSetConstantBuffers(0, 1, &this->cbuffer_);
		d3d->context_->PSSetConstantBuffers(0, 1, &this->cbuffer_);

		D3D11_MAPPED_SUBRESOURCE data;
		if (SUCCEEDED(d3d->context_->Map(this->cbuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &data)))
		{
			memcpy_s(data.pData, data.RowPitch, this->cb_, cb_size);
			d3d->context_->Unmap(this->cbuffer_, 0);
		}
	}

	template<class _CBUFFER>
	void MakeShader(std::string hlsl, D3D11_INPUT_ELEMENT_DESC * desc, int desc_num)
	{
		auto d3d = Game::GetSystem<System::Direct3D11>();

		ID3DBlob * compiled_shader = nullptr;
		ID3DBlob * errors = nullptr;

		{// �o�[�e�b�N�V�F�[�_�[�쐬
			if (FAILED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "VS", "vs_5_0",
				D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
			{
				errors ? Utils::EndMsg((char*)errors->GetBufferPointer()) : Utils::EndMsg("VS�V�F�[�_�t�@�C����������܂���ł���");
				return;
			}
			else
			{
				if (FAILED(d3d->device_->CreateVertexShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->vs_)))
					Utils::EndMsg("VS�̐����Ɏ��s���܂���");
			}
			Utils::Memory::SafeRelease(errors);
		}

		{// �C���v�b�g���C�A�E�g�쐬
			if (FAILED(d3d->device_->CreateInputLayout(desc, desc_num, compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), &this->layout_)))
				Utils::EndMsg("�C���v�b�g���C�A�E�g�̐����Ɏ��s���܂����B");

			Utils::Memory::SafeRelease(compiled_shader);
		}

		{// �W�I���g���V�F�[�_�[�쐬
			if (SUCCEEDED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "GS", "gs_5_0",
				D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
				if (FAILED(d3d->device_->CreateGeometryShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->gs_)))
					Utils::EndMsg("GS�̐����Ɏ��s���܂����B");

			Utils::Memory::SafeRelease(errors);
		}

		{// �s�N�Z���V�F�[�_�[�쐬
			if (FAILED(D3DX11CompileFromFileA(hlsl.c_str(), nullptr, nullptr, "PS", "ps_5_0",
				D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, nullptr, &compiled_shader, &errors, nullptr)))
				errors ? Utils::EndMsg((char*)errors->GetBufferPointer()) : Utils::EndMsg("PS�V�F�[�_�t�@�C����������܂���ł���");
			else
				if (FAILED(d3d->device_->CreatePixelShader(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), nullptr, &this->ps_)))
					Utils::EndMsg("PS�̐����Ɏ��s���܂����B");

			Utils::Memory::SafeRelease(errors);
		}

		{//�R���X�^���g�o�b�t�@�[�쐬
			D3D11_BUFFER_DESC cb;
			cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			cb.ByteWidth = sizeof(_CBUFFER);
			cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			cb.MiscFlags = 0;
			cb.StructureByteStride = 0;
			cb.Usage = D3D11_USAGE_DYNAMIC;

			d3d->device_->CreateBuffer(&cb, nullptr, &this->cbuffer_);
		}
	}
};