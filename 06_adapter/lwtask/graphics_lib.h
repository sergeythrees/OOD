#pragma once
// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
};
}