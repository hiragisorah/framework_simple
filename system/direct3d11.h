#pragma once

// �G���[������(�Œ��)
#pragma warning(disable: 4005) //�}�N���Ē�`

// �t���[�����[�N
#include <framework\system.h>
#include <system\window.h>
#include <utils\memory.h>
#include <framework\entity.h>

// �R���|�[�l���g
#include <component\renderer.h>

// API
#include <D3DX11.h>
#include <D3DX10.h>

// �W�����C�u����
#include <algorithm>

// ���C�u�����t�@�C���Ǎ�
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx10.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dCompiler.lib")

namespace System
{
	class Direct3D11 : public ISystem
	{
	public:
		ID3D11Device * device_;
		ID3D11DeviceContext * context_;
		IDXGISwapChain * swap_chain_;
		ID3D11Texture2D * back_buffer_ds_tex_;
		ID3D11RenderTargetView * back_buffer_rtv_;
		ID3D11DepthStencilView * back_buffer_dsv_;
		D3DXCOLOR bg_color_ = { 0.5f, 0.4f, 1.f, 1.f };
		std::vector<Component::IRenderer*> draw_list_;

	public:
		Direct3D11(void)
		{
			// window�V�X�e���̎擾
			auto window = Game::GetSystem<Window>();

			{// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
				DXGI_SWAP_CHAIN_DESC sd;
				ZeroMemory(&sd, sizeof(sd));
				sd.BufferCount = 1;
				sd.BufferDesc.Width = window->Width();
				sd.BufferDesc.Height = window->Height();
				sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				sd.BufferDesc.RefreshRate.Numerator = 60;
				sd.BufferDesc.RefreshRate.Denominator = 1;
				sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				sd.OutputWindow = window->Hwnd();
				sd.SampleDesc.Count = 1;
				sd.SampleDesc.Quality = 0;
				sd.Windowed = true;

				D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
				D3D_FEATURE_LEVEL * feature_level = nullptr;

				D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
					0, &feature_levels, 1, D3D11_SDK_VERSION, &sd, &this->swap_chain_, &this->device_,
					feature_level, &this->context_);
			}

			{// �e��e�N�X�`���[�ƁA����ɕt�т���e��r���[���쐬


				{// �o�b�N�o�b�t�@�[�e�N�X�`���[���擾
					ID3D11Texture2D * back_buffer_tex;
					this->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_tex);

					{// ���̃e�N�X�`���[�ɑ΂������_�[�^�[�Q�b�g�r���[(RTV)���쐬
						this->device_->CreateRenderTargetView(back_buffer_tex, nullptr, &this->back_buffer_rtv_);
						Utils::Memory::SafeRelease(back_buffer_tex);
					}
				}

				{// �f�v�X�X�e���V���r���[�p�̃e�N�X�`���[���쐬
					D3D11_TEXTURE2D_DESC descDepth;
					descDepth.Width = window->Width();
					descDepth.Height = window->Height();
					descDepth.MipLevels = 1;
					descDepth.ArraySize = 1;
					descDepth.Format = DXGI_FORMAT_D32_FLOAT;
					descDepth.SampleDesc.Count = 1;
					descDepth.SampleDesc.Quality = 0;
					descDepth.Usage = D3D11_USAGE_DEFAULT;
					descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
					descDepth.CPUAccessFlags = 0;
					descDepth.MiscFlags = 0;
					this->device_->CreateTexture2D(&descDepth, nullptr, &this->back_buffer_ds_tex_);

					{// ���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[(DSV)���쐬
						this->device_->CreateDepthStencilView(this->back_buffer_ds_tex_, nullptr, &this->back_buffer_dsv_);
					}

					{// �����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���p�C�v���C���ɃZ�b�g
						this->context_->OMSetRenderTargets(1, &this->back_buffer_rtv_, this->back_buffer_dsv_);
					}
				}
			}

			{// �r���[�|�[�g�̍쐬
				D3D11_VIEWPORT vp;
				vp.Width = window->Width<float>();
				vp.Height = window->Height<float>();
				vp.MinDepth = 0.0f;
				vp.MaxDepth = 1.0f;
				vp.TopLeftX = 0;
				vp.TopLeftY = 0;

				{// �r���[�|�[�g��ݒ�
					this->context_->RSSetViewports(1, &vp);
				}
			}

		}
		~Direct3D11(void)
		{
			Utils::Memory::SafeRelease(this->back_buffer_dsv_);
			Utils::Memory::SafeRelease(this->back_buffer_rtv_);
			Utils::Memory::SafeRelease(this->back_buffer_ds_tex_);
			Utils::Memory::SafeRelease(this->swap_chain_);
			Utils::Memory::SafeRelease(this->context_);
			Utils::Memory::SafeRelease(this->device_);
		}

		void Update(void) override
		{
			{// ��ʃN���A
				this->context_->ClearRenderTargetView(this->back_buffer_rtv_, this->bg_color_);//�J���[�o�b�t�@�N���A
				this->context_->ClearDepthStencilView(this->back_buffer_dsv_, D3D11_CLEAR_DEPTH, 1.0f, 0);//�f�v�X�X�e���V���o�b�t�@�N���A
			}

			{// �`��
				for (auto draw : this->draw_list_)
					draw->Rendering();

				this->draw_list_.clear();
			}

			{// ��ʍX�V
				this->swap_chain_->Present(1, 0);
			}
		}
	};
}