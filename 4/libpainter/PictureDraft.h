#pragma once
#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include "Shape.h"



class CPictureDraft
{

public:
	typedef std::vector<std::unique_ptr<CShape>> Storage;


	CPictureDraft();

	bool IsEmpty()const;

	typedef boost::indirect_iterator<Storage::const_iterator, const CShape&> ConstIterator;

	ConstIterator begin()const;

	ConstIterator end()const;

	void AddShape(std::unique_ptr<CShape> && shape);
	size_t GetShapeCount() const { return m_shapes.size(); }
	const CShape& GetShape(size_t index) const { return *m_shapes[index]; }

	CPictureDraft(CPictureDraft &&) = default;
	CPictureDraft& operator=(CPictureDraft &&) = default;

	CPictureDraft(const CPictureDraft &) = delete;
	CPictureDraft& operator=(const CPictureDraft &) = delete;
private:
	Storage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft & draft)
{
	return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft & draft)
{
	return draft.end();
}
