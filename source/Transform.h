//#pragma once
//#include "DirectX.h"
//
//struct Transform {
//public:
//	D3DXVECTOR3 position, rotation, scale;
//	
//	D3DXMATRIX &GetWorldMatrix() {
//		D3DXMATRIX worldMatrix;
//		D3DXMATRIX positionMatrix, rotationMatrix, scaleMatrix;
//		D3DXMatrixScaling(&scaleMatrix, position.x, position.y, position.z);
//		D3DXMatrixRotationX(&rotationMatrix, g_angle);
//		D3DXMatrixTranslation(&positionMatrix, 0.0f, 0.0f, 0.0f);
//	}
//};