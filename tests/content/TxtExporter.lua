function bool_to_string(boolean)
    if boolean then
        return "true"
    else
        return "false"
    end
end

function export(textures, width, height, imagePath, outputDirectory, outputName)

    local path = ""
    if outputDirectory ~= "" then
        path = outputDirectory .. "/" .. outputName .. ".txt"
    else
        path = "./" .. outputName .. ".txt"
    end

    file = io.open(path, "w")

    file:write("img=\"" .. imagePath .. "\",")
    file:write("w=\"" .. tostring(width) .. "\",")
    file:write("h=\"" .. tostring(height) .. "\"\n")

    for i = 1, #textures, 1 do
        local current = textures[i]
        file:write("key=\"" .. (convert(current.path)) .. "\",")
        
        file:write("x=\"" .. tostring(current.bounds.left) .. "\",")
        file:write("y=\"" .. tostring(current.bounds.top) .. "\",")
        file:write("w=\"" .. tostring(current.bounds.width) .. "\",")
        file:write("h=\"" .. tostring(current.bounds.height) .. "\",")

        file:write("ox=\"" .. tostring(current.offsetX) .. "\",")
        file:write("oy=\"" .. tostring(current.offsetY) .. "\",")
        file:write("sw=\"" .. tostring(current.sourceWidth) .. "\",")
        file:write("sh=\"" .. tostring(current.sourceHeight) .. "\",")

        file:write("r=\"" .. bool_to_string(current.bounds.rotated) .. "\"\n")
    end
end
