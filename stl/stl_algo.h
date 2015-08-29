template <class InputIterator, class T>
InputIterator find(InputIterator first,
					InputIteraator last,
					const T& value)
{
	while(first != last && *first != value)
		++first;
	return first;
}
