# Icinga 2
# Copyright (C) 2012-2014 Icinga Development Team (http://www.icinga.org)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

find_package(BISON 2.3.0 REQUIRED)
find_package(FLEX 2.5.31 REQUIRED)

bison_target(config_parser config_parser.yy ${CMAKE_CURRENT_BINARY_DIR}/config_parser.cc)
flex_target(config_lexer config_lexer.ll ${CMAKE_CURRENT_BINARY_DIR}/config_lexer.cc)
add_flex_bison_dependency(config_lexer config_parser)

mkembedconfig_target(base-type.conf base-type.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_library(config SHARED
  aexpression.cpp applyrule.cpp avalue.cpp base-type.conf base-type.cpp
  configcompilercontext.cpp configcompiler.cpp configerror.cpp configitembuilder.cpp
  configitem.cpp ${FLEX_config_lexer_OUTPUTS} ${BISON_config_parser_OUTPUTS}
  configtype.cpp debuginfo.cpp expression.cpp expressionlist.cpp typerule.cpp typerulelist.cpp
)

target_link_libraries(config ${Boost_LIBRARIES} base) 

set_target_properties (
  config PROPERTIES
  INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR}/icinga2
  DEFINE_SYMBOL I2_CONFIG_BUILD
  FOLDER Lib
)

install(
  TARGETS config
  RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/icinga2
)
