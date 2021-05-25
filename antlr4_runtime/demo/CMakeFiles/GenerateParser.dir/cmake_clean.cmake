file(REMOVE_RECURSE
  "CMakeFiles/GenerateParser"
  "generated/TLexer.cpp"
  "generated/TParser.cpp"
  "generated/TParserBaseListener.cpp"
  "generated/TParserBaseVisitor.cpp"
  "generated/TParserListener.cpp"
  "generated/TParserVisitor.cpp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/GenerateParser.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
