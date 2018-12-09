local function get_file_name_without_ext(path)
	local dotIndex = path:find(".", 1, true)
	if dotIndex == nil then dotIndex = path:len() end
	
	local slashIndex = nil

    for i = path:len(), 1, -1 do
		if path:sub(i, i) == "/" then
			slashIndex = i
			break
		end
	end

	if slashIndex == nil then slashIndex = 0 end

	return path:sub(slashIndex + 1, dotIndex - 1)
end

local function all_caps_underscore_seperated(path)
	local output = get_file_name_without_ext(path)
	return output:upper()
end

function export(textures, width, height, imagePath, outputDirectory, outputName)
    local path = ""
    if outputDirectory ~= "" then
        path = outputDirectory .. "/" .. outputName .. ".hpp"
    else
        path = "./" .. outputName .. ".hpp"
    end

    file = io.open(path, "w")

    file:write("#pragma once\n\n")

    for i = 1, #textures, 1 do
        local current = textures[i]
        file:write("#define " .. all_caps_underscore_seperated(current.path))
		file:write(" " .. convert(current.path) .. "\n")
    end
end
