#pragma once

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString);
void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString);
