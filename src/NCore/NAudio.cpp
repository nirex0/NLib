// © 2018 NIREX ALL RIGHTS RESERVED

#include "NAudio.h"

namespace NLib
{
	NAudio::NAudio(const wchar_t* name, const wchar_t* path, HWND handle)
		: m_name(name)
		, m_path(path)
		, m_handle(handle)
	{
		std::wstring cmd = L"";
		cmd += L"open \"";
		cmd += m_path;
		cmd += L"\" type mpegvideo alias ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	NAudio::~NAudio(void)
	{
		std::wstring cmd = L"";
		cmd = L"";
		cmd += L"close ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	const wchar_t* NAudio::Path(void) const
	{
		return m_path;
	}

	const wchar_t* NAudio::Name(void) const
	{
		return m_name;
	}

	void NAudio::Play(void)
	{
		std::wstring cmd = L"";
		cmd += L"stop ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);

		cmd = L"";
		cmd += L"play ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	void NAudio::Pause(void)
	{
		std::wstring cmd = L"";
		cmd += L"pause ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	void NAudio::Resume(void)
	{
		std::wstring cmd = L"";
		cmd += L"resume ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	void NAudio::Stop(void)
	{
		std::wstring cmd = L"";
		cmd += L"stop ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}

	void NAudio::PlayOnRepeat(void)
	{
		std::wstring cmd = L"";
		cmd += L"stop ";
		cmd += m_name;
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);

		cmd = L"";
		cmd += L"play ";
		cmd += m_name;
		cmd += L" repeat";
		mciSendString(cmd.c_str(), nullptr, 0, m_handle);
	}
}
