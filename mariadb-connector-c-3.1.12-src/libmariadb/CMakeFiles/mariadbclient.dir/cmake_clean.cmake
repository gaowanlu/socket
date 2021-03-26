file(REMOVE_RECURSE
  "libmariadbclient.pdb"
  "libmariadbclient.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/mariadbclient.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
