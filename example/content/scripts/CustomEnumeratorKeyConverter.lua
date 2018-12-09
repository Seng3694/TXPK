local i = 0

function convert(input)
	str = tostring(i)
	i = i + 1
	return str
end

function reset()
	i = 0
end
