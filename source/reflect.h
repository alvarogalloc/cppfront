
#ifndef REFLECT_H__CPP2
#define REFLECT_H__CPP2


//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"


#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 32 "reflect.h2"
class compiler_services;

#line 186 "reflect.h2"
class declaration_base;

#line 212 "reflect.h2"
class declaration;

#line 276 "reflect.h2"
class function_declaration;

#line 333 "reflect.h2"
class object_declaration;

#line 369 "reflect.h2"
class type_declaration;

#line 471 "reflect.h2"
class alias_declaration;

#line 818 "reflect.h2"
class value_member_info;

#line 1214 "reflect.h2"
}
}


//=== Cpp2 type definitions and function declarations ===========================


//  Copyright (c) Herb Sutter
//  SPDX-License-Identifier: CC-BY-NC-ND-4.0

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


//===========================================================================
//  Reflection and meta
//===========================================================================

#include "parse.h"

#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 25 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Compiler services
//
//-----------------------------------------------------------------------
//

class compiler_services
 {
    private: std::vector<error_entry>* errors; 
    private: int errors_original_size; 
    private: std::deque<token>* generated_tokens; 
    private: cpp2::parser parser; 
    private: std::string metafunction_name {}; 
    private: std::vector<std::string> metafunction_args {}; 

    public: explicit compiler_services(

        std::vector<error_entry>* errors_, 
        std::deque<token>* generated_tokens_
    );

#line 53 "reflect.h2"
    public: auto set_metafunction_name(cpp2::in<std::string_view> name, cpp2::in<std::vector<std::string>> args) & -> void;
        

#line 58 "reflect.h2"
    public: [[nodiscard]] auto get_argument(cpp2::in<cpp2::i16> index) const& -> std::string;
        

#line 65 "reflect.h2"
    protected: [[nodiscard]] auto parse_statement(

        std::string_view source
    ) & -> 
        std::unique_ptr<statement_node>;

#line 113 "reflect.h2"
    public: [[nodiscard]] virtual auto position() const& -> 
        source_position; 

#line 119 "reflect.h2"
    public: auto require(

        cpp2::in<bool> b, 
        cpp2::in<std::string_view> msg
    ) const& -> void;

#line 130 "reflect.h2"
    public: auto error(cpp2::in<std::string_view> msg) const& -> void;
    
    public: virtual ~compiler_services() noexcept;
public: compiler_services(compiler_services const& that);


#line 138 "reflect.h2"
};

/*
//-----------------------------------------------------------------------
//
//  Type IDs
//
//-----------------------------------------------------------------------
//

//  All type_ids are wrappers around a pointer to node
//
type_id: @polymorphic_base @copyable type =
{
    this: compiler_services = ();

    n: type_id_node;

    protected operator=: (
        out this,
        n_: type_id_node,
        s : compiler_services
    )
    = {
        compiler_services = s;
        n = n_;
        [[assert: n, "a meta::type_id must point to a valid type_id_node, not null"]]
    }

    is_wildcard         : (this) -> bool        = n.is_wildcard();
    is_pointer_qualified: (this) -> bool        = n.is_pointer_qualified();
    template_args_count : (this) -> int         = n.template_arguments().ssize();
    to_string           : (this) -> std::string = n.to_string();

    position: (override this) -> source_position = n.position();
}
*/

#line 177 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Declarations
//
//-----------------------------------------------------------------------
//

//  All declarations are wrappers around a pointer to node
//
class declaration_base
: public compiler_services {

#line 190 "reflect.h2"
    protected: declaration_node* n; 

    protected: explicit declaration_base(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 203 "reflect.h2"
    public: [[nodiscard]] auto position() const& -> source_position override;

    public: [[nodiscard]] auto print() const& -> std::string;

public: virtual ~declaration_base() noexcept;
public: declaration_base(declaration_base const& that);
#line 206 "reflect.h2"
};

#line 209 "reflect.h2"
//-----------------------------------------------------------------------
//  All declarations
//
class declaration
: public declaration_base {

#line 216 "reflect.h2"
    public: explicit declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 225 "reflect.h2"
    public: [[nodiscard]] auto is_public() const& -> bool;
    public: [[nodiscard]] auto is_protected() const& -> bool;
    public: [[nodiscard]] auto is_private() const& -> bool;
    public: [[nodiscard]] auto is_default_access() const& -> bool;

    public: auto default_to_public() & -> void;
    public: auto default_to_protected() & -> void;
    public: auto default_to_private() & -> void;

    public: [[nodiscard]] auto make_public() & -> bool;
    public: [[nodiscard]] auto make_protected() & -> bool;
    public: [[nodiscard]] auto make_private() & -> bool;

    public: [[nodiscard]] auto has_name() const& -> bool;
    public: [[nodiscard]] auto has_name(cpp2::in<std::string_view> s) const& -> bool;

    public: [[nodiscard]] auto name() const& -> std::string_view;
        

#line 246 "reflect.h2"
    public: [[nodiscard]] auto has_initializer() const& -> bool;

    public: [[nodiscard]] auto is_global() const& -> bool;
    public: [[nodiscard]] auto is_function() const& -> bool;
    public: [[nodiscard]] auto is_object() const& -> bool;
    public: [[nodiscard]] auto is_type() const& -> bool;
    public: [[nodiscard]] auto is_namespace() const& -> bool;
    public: [[nodiscard]] auto is_alias() const& -> bool;

    public: [[nodiscard]] auto is_function_expression() const& -> bool;

    public: [[nodiscard]] auto as_function() const& -> function_declaration;
    public: [[nodiscard]] auto as_object() const& -> object_declaration;
    public: [[nodiscard]] auto as_type() const& -> type_declaration;
    public: [[nodiscard]] auto as_alias() const& -> alias_declaration;

    public: [[nodiscard]] auto get_parent() const& -> declaration;

    public: [[nodiscard]] auto parent_is_function() const& -> bool;
    public: [[nodiscard]] auto parent_is_object() const& -> bool;
    public: [[nodiscard]] auto parent_is_type() const& -> bool;
    public: [[nodiscard]] auto parent_is_namespace() const& -> bool;
    public: [[nodiscard]] auto parent_is_alias() const& -> bool;
    public: [[nodiscard]] auto parent_is_polymorphic() const& -> bool;

public: virtual ~declaration() noexcept;
public: declaration(declaration const& that);
#line 270 "reflect.h2"
};

#line 273 "reflect.h2"
//-----------------------------------------------------------------------
//  Function declarations
//
class function_declaration
: public declaration {

#line 280 "reflect.h2"
    public: explicit function_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 290 "reflect.h2"
    public: [[nodiscard]] auto index_of_parameter_named(cpp2::in<std::string_view> s) const& -> int;
    public: [[nodiscard]] auto has_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_in_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_out_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_move_parameter_named(cpp2::in<std::string_view> s) const& -> bool;

    public: [[nodiscard]] auto has_parameter_with_name_and_pass(cpp2::in<std::string_view> s, cpp2::in<passing_style> pass) const& -> bool;
                                                  
    public: [[nodiscard]] auto is_function_with_this() const& -> bool;
    public: [[nodiscard]] auto is_virtual() const& -> bool;
    public: [[nodiscard]] auto is_defaultable() const& -> bool;
    public: [[nodiscard]] auto is_constructor() const& -> bool;
    public: [[nodiscard]] auto is_default_constructor() const& -> bool;
    public: [[nodiscard]] auto is_move() const& -> bool;
    public: [[nodiscard]] auto is_swap() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_destructor() const& -> bool;

    public: [[nodiscard]] auto is_copy_or_move() const& -> bool;

    public: [[nodiscard]] auto has_declared_return_type() const& -> bool;
    public: [[nodiscard]] auto has_bool_return_type() const& -> bool;
    public: [[nodiscard]] auto has_non_void_return_type() const& -> bool;

    public: [[nodiscard]] auto unnamed_return_type() const& -> std::string;

    public: [[nodiscard]] auto is_binary_comparison_function() const& -> bool;

    public: auto default_to_virtual() & -> void;

    public: [[nodiscard]] auto make_virtual() & -> bool;

public: function_declaration(function_declaration const& that);
#line 327 "reflect.h2"
};

#line 330 "reflect.h2"
//-----------------------------------------------------------------------
//  Object declarations
//
class object_declaration
: public declaration {

#line 337 "reflect.h2"
    public: explicit object_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 347 "reflect.h2"
    public: [[nodiscard]] auto is_const() const& -> bool;
    public: [[nodiscard]] auto has_wildcard_type() const& -> bool;

    public: [[nodiscard]] auto type() const& -> std::string;
        

#line 357 "reflect.h2"
    public: [[nodiscard]] auto initializer() const& -> std::string;
        
        public: object_declaration(object_declaration const& that);


#line 363 "reflect.h2"
};

#line 366 "reflect.h2"
//-----------------------------------------------------------------------
//  Type declarations
//
class type_declaration
: public declaration {

#line 373 "reflect.h2"
    public: explicit type_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 383 "reflect.h2"
    public: [[nodiscard]] auto is_polymorphic() const& -> bool;
    public: [[nodiscard]] auto is_final() const& -> bool;
    public: [[nodiscard]] auto make_final() & -> bool;

    public: [[nodiscard]] auto get_member_functions() const& -> 
        std::vector<function_declaration>; 

#line 397 "reflect.h2"
    public: [[nodiscard]] auto get_member_objects() const& -> 
        std::vector<object_declaration>; 

#line 407 "reflect.h2"
    public: [[nodiscard]] auto get_member_types() const& -> 
        std::vector<type_declaration>; 

#line 417 "reflect.h2"
    public: [[nodiscard]] auto get_member_aliases() const& -> 
        std::vector<alias_declaration>; 

#line 427 "reflect.h2"
    public: [[nodiscard]] auto get_members() const& -> 
        std::vector<declaration>; struct query_declared_value_set_functions__ret { bool out_this_in_that; bool out_this_move_that; bool inout_this_in_that; bool inout_this_move_that; };



#line 437 "reflect.h2"
    public: [[nodiscard]] auto query_declared_value_set_functions() const& -> query_declared_value_set_functions__ret;
        

#line 452 "reflect.h2"
    public: [[nodiscard]] auto add_member(cpp2::in<std::string_view> source) & -> 
        bool; 

#line 462 "reflect.h2"
    public: auto remove_all_members() & -> void;

    public: auto disable_member_function_generation() & -> void;

public: type_declaration(type_declaration const& that);
#line 465 "reflect.h2"
};

#line 468 "reflect.h2"
//-----------------------------------------------------------------------
//  Alias declarations
//
class alias_declaration
: public declaration {

#line 475 "reflect.h2"
    public: explicit alias_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    );

#line 485 "reflect.h2"
    public: [[nodiscard]] auto is_type_alias() const& -> bool;
    public: [[nodiscard]] auto is_namespace_alias() const& -> bool;
    public: [[nodiscard]] auto is_object_alias() const& -> bool;

public: alias_declaration(alias_declaration const& that);
#line 488 "reflect.h2"
};

#line 491 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Metafunctions - these are hardwired for now until we get to the
//  step of writing a Cpp2 interpreter to run inside the compiler
//
//-----------------------------------------------------------------------
//

//-----------------------------------------------------------------------
//  Some common metafunction helpers (metafunctions are just functions,
//  so they can be factored as usual)
//
auto add_virtual_destructor(meta::type_declaration& t) -> void;

#line 510 "reflect.h2"
//-----------------------------------------------------------------------
//
//      "... an abstract base class defines an interface ..."
//
//          -- Stroustrup (The Design and Evolution of C++, 12.3.1)
//
//-----------------------------------------------------------------------
//
//  interface
//
//  an abstract base class having only pure virtual functions
//
auto interface(meta::type_declaration& t) -> void;

#line 549 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C.35: A base class destructor should be either public and
//      virtual, or protected and non-virtual."
//
//     "[C.43] ... a base class should not be copyable, and so does not
//      necessarily need a default constructor."
//
//          -- Stroustrup, Sutter, et al. (C++ Core Guidelines)
//
//-----------------------------------------------------------------------
//
//  polymorphic_base
//
//  A pure polymorphic base type that is not copyable, and whose
//  destructor is either public and virtual or protected and nonvirtual.
//
//  Unlike an interface, it can have nonpublic and nonvirtual functions.
//
auto polymorphic_base(meta::type_declaration& t) -> void;

#line 593 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "... A totally ordered type ... requires operator<=> that
//      returns std::strong_ordering. If the function is not
//      user-written, a lexicographical memberwise implementation
//      is generated by default..."
//
//          -- P0707R4, section 3
//
//      Note: This feature derived from Cpp2 was already adopted
//            into Standard C++ via paper P0515, so most of the
//            heavy lifting is done by the Cpp1 C++20/23 compiler,
//            including the memberwise default semantics
//            (In contrast, cppfront has to do the work itself for
//            default memberwise semantics for operator= assignment
//            as those aren't yet part of Standard C++)
//
//-----------------------------------------------------------------------
//

auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::in<std::string_view> ordering// must be "strong_ordering" etc.
) -> void;

#line 638 "reflect.h2"
//-----------------------------------------------------------------------
//  ordered - a totally ordered type
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto ordered(meta::type_declaration& t) -> void;

#line 648 "reflect.h2"
//-----------------------------------------------------------------------
//  weakly_ordered - a weakly ordered type
//
auto weakly_ordered(meta::type_declaration& t) -> void;

#line 656 "reflect.h2"
//-----------------------------------------------------------------------
//  partially_ordered - a partially ordered type
//
auto partially_ordered(meta::type_declaration& t) -> void;

#line 665 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A value is ... a regular type. It must have all public
//      default construction, copy/move construction/assignment,
//      and destruction, all of which are generated by default
//      if not user-written; and it must not have any protected
//      or virtual functions (including the destructor)."
//
//          -- P0707R4, section 3
//
//-----------------------------------------------------------------------
//
//  copyable
//
//  A type with (copy and move) x (construction and assignment)
//
auto copyable(meta::type_declaration& t) -> void;

#line 703 "reflect.h2"
//-----------------------------------------------------------------------
//
//  basic_value
//
//  A regular type: copyable, plus has public default construction
//  and no protected or virtual functions
//
auto basic_value(meta::type_declaration& t) -> void;

#line 729 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A 'value' is a totally ordered basic_value..."
// 
//          -- P0707R4, section 3
//
//  value - a value type that is totally ordered
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto value(meta::type_declaration& t) -> void;

#line 745 "reflect.h2"
auto weakly_ordered_value(meta::type_declaration& t) -> void;

#line 751 "reflect.h2"
auto partially_ordered_value(meta::type_declaration& t) -> void;

#line 758 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "By definition, a `struct` is a `class` in which members
//      are by default `public`; that is,
//
//      	struct s { ...
//
//      is simply shorthand for
//
//          class s { public: ...
//
//      ... Which style you use depends on circumstances and taste.
//      I usually prefer to use `struct` for classes that have all
//      data `public`."
//
//          -- Stroustrup (The C++ Programming Language, 3rd ed., p. 234)
//
//-----------------------------------------------------------------------
//
//  struct
//
//  a type with only public bases, objects, and functions,
//  no virtual functions, and no user-defined constructors
//  (i.e., no invariants) or assignment or destructors.
//
auto cpp2_struct(meta::type_declaration& t) -> void;

#line 801 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C enumerations constitute a curiously half-baked concept. ...
//      the cleanest way out was to deem each enumeration a separate type."
//
//          -- Stroustrup (The Design and Evolution of C++, 11.7)
//
//     "An enumeration is a distinct type ... with named constants"
//
//          -- ISO C++ Standard
//
//-----------------------------------------------------------------------
//
//  basic_enum
//
//  a type together with named constants that are its possible values
//
class value_member_info {
    public: std::string name; 
    public: std::string type; 
    public: std::string value; 
};
struct basic_enum__ret { std::string underlying_type; std::string strict_underlying_type; };

#line 824 "reflect.h2"
[[nodiscard]] auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::in<bool> bitwise
    ) -> basic_enum__ret;

#line 998 "reflect.h2"
//-----------------------------------------------------------------------
//
//    "An enum[...] is a totally ordered value type that stores a
//     value of its enumerators's type, and otherwise has only public
//     member variables of its enumerator's type, all of which are
//     naturally scoped because they are members of a type."
// 
//          -- P0707R4, section 3
//
auto cpp2_enum(meta::type_declaration& t) -> void;

#line 1024 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "flag_enum expresses an enumeration that stores values 
//      corresponding to bitwise-or'd enumerators. The enumerators must
//      be powers of two, and are automatically generated [...] A none
//      value is provided [...] Operators | and & are provided to
//      combine and extract values."
// 
//          -- P0707R4, section 3
//
auto flag_enum(meta::type_declaration& t) -> void;

#line 1060 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "As with void*, programmers should know that unions [...] are
//      inherently dangerous, should be avoided wherever possible,
//      and should be handled with special care when actually needed."
//
//          -- Stroustrup (The Design and Evolution of C++, 14.3.4.1)
//
//     "C++17 needs a type-safe union... The implications of the 
//      consensus `variant` design are well understood and have been 
//      explored over several LEWG discussions, over a thousand emails, 
//      a joint LEWG/EWG session, and not to mention 12 years of 
//      experience with Boost and other libraries."
//
//          -- Axel Naumann, in P0088 (wg21.link/p0088),
//             the adopted proposal for C++17 std::variant
//
//-----------------------------------------------------------------------
//
//  union
// 
//  a type that contains exactly one of a fixed set of values at a time
// 

auto cpp2_union(meta::type_declaration& t) -> void;

#line 1202 "reflect.h2"
//-----------------------------------------------------------------------
//
//  print - output a pretty-printed visualization of t
//
auto print(cpp2::in<meta::type_declaration> t) -> void;

#line 1212 "reflect.h2"
//=======================================================================
//  Switch to Cpp1 and close subnamespace meta
}
}
namespace cpp2 {


//-----------------------------------------------------------------------
//
//  Now finish the rest of the parser definition
//
//-----------------------------------------------------------------------
//

auto parser::apply_type_metafunctions( declaration_node& n )
    -> bool
{
    assert(n.is_type());

    //  Get the reflection state ready to pass to the function
    auto cs = meta::compiler_services{ &errors, generated_tokens };
    auto rtype = meta::type_declaration{ &n, cs };

    //  For each metafunction, apply it
    for (auto& meta : n.metafunctions)
    {
        //  Convert the name and any template arguments to strings
        //  and record that in rtype
        auto name = meta->to_string();
        name = name.substr(0, name.find('<'));

        auto args = std::vector<std::string>{};
        for (auto& arg : meta->template_arguments()) {
            args.push_back( arg.to_string() );
        }

        rtype.set_metafunction_name( name, args );

        //  Dispatch
        //
        if (name == "interface") {
            interface( rtype );
        }
        else if (name == "polymorphic_base") {
            polymorphic_base( rtype );
        }
        else if (name == "ordered") {
            ordered( rtype );
        }
        else if (name == "weakly_ordered") {
            weakly_ordered( rtype );
        }
        else if (name == "partially_ordered") {
            partially_ordered( rtype );
        }
        else if (name == "copyable") {
            copyable( rtype );
        }
        else if (name == "basic_value") {
            basic_value( rtype );
        }
        else if (name == "value") {
            value( rtype );
        }
        else if (name == "weakly_ordered_value") {
            weakly_ordered_value( rtype );
        }
        else if (name == "partially_ordered_value") {
            partially_ordered_value( rtype );
        }
        else if (name == "struct") {
            cpp2_struct( rtype );
        }
        else if (name == "enum") {
            cpp2_enum( rtype );
        }
        else if (name == "flag_enum") {
            flag_enum( rtype );
        }
        else if (name == "union") {
            cpp2_union( rtype );
        }
        else if (name == "print") {
            print( rtype );
        }
        else {
            error( "(temporary alpha limitation) unrecognized metafunction name '" + name + "' - currently the supported names are: interface, polymorphic_base, ordered, weakly_ordered, partially_ordered, copyable, basic_value, value, weakly_ordered_value, partially_ordered_value, struct, enum, flag_enum, union, print" );
            return false;
        }
    }
    return true;
}


}


//=== Cpp2 function definitions =================================================


#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 41 "reflect.h2"
    compiler_services::compiler_services(

        std::vector<error_entry>* errors_, 
        std::deque<token>* generated_tokens_
    )
        : errors{ errors_ }
        , errors_original_size{ cpp2::unsafe_narrow<int>(std::ssize(*cpp2::assert_not_null(errors))) }
        , generated_tokens{ generated_tokens_ }
        , parser{ *cpp2::assert_not_null(errors) }
#line 46 "reflect.h2"
    {

#line 51 "reflect.h2"
    }

    auto compiler_services::set_metafunction_name(cpp2::in<std::string_view> name, cpp2::in<std::vector<std::string>> args) & -> void{
        metafunction_name = name;
        metafunction_args = args;
    }

    [[nodiscard]] auto compiler_services::get_argument(cpp2::in<cpp2::i16> index) const& -> std::string{
        if (([_0 = 0, _1 = index, _2 = CPP2_UFCS_0(ssize, metafunction_args)]{ return cpp2::cmp_less_eq(_0,_1) && cpp2::cmp_less(_1,_2); }())) {
            return cpp2::assert_in_bounds(metafunction_args, index); 
        }
        return ""; 
    }

    [[nodiscard]] auto compiler_services::parse_statement(

        std::string_view source
    ) & -> 
        std::unique_ptr<statement_node>
    {
        CPP2_UFCS(push_back, generated_lines, std::vector<source_line>());
        auto lines {&CPP2_UFCS_0(back, generated_lines)}; 

        auto add_line {[&, _1 = lines](cpp2::in<std::string_view> s) -> void{
            static_cast<void>(CPP2_UFCS(emplace_back, (*cpp2::assert_not_null(_1)), s, source_line::category::cpp2));
        }}; 
{
auto newline_pos = CPP2_UFCS(find, source, '\n');

        //  First split this string into source_lines
        //

#line 81 "reflect.h2"
        if ( cpp2::cmp_greater(CPP2_UFCS_0(ssize, source),1) 
            && newline_pos != source.npos) 
        {
            while( newline_pos != std::string_view::npos ) 
            {
                add_line(CPP2_UFCS(substr, source, 0, newline_pos));
                CPP2_UFCS(remove_prefix, source, newline_pos + 1);
                newline_pos = CPP2_UFCS(find, source, '\n');
            }
        }
}

#line 92 "reflect.h2"
        if (!(CPP2_UFCS_0(empty, source))) {
            std::move(add_line)(std::move(source));
        }

        //  Now lex this source fragment to generate
        //  a single grammar_map entry, whose .second
        //  is the vector of tokens
        static_cast<void>(CPP2_UFCS(emplace_back, generated_lexers, *cpp2::assert_not_null(errors)));
        auto tokens {&CPP2_UFCS_0(back, generated_lexers)}; 
        CPP2_UFCS(lex, (*cpp2::assert_not_null(tokens)), *cpp2::assert_not_null(std::move(lines)), true);

        cpp2::Default.expects(std::ssize(CPP2_UFCS_0(get_map, (*cpp2::assert_not_null(tokens)))) == 1, "");

        //  Now parse this single declaration from
        //  the lexed tokens
        return CPP2_UFCS(parse_one_declaration, parser, 
            (*cpp2::assert_not_null(CPP2_UFCS_0(begin, CPP2_UFCS_0(get_map, *cpp2::assert_not_null(std::move(tokens)))))).second, 
            *cpp2::assert_not_null(generated_tokens)
        ); 
    }

    [[nodiscard]] auto compiler_services::position() const& -> 
        source_position
    {
        return {  }; 
    }

    auto compiler_services::require(

        cpp2::in<bool> b, 
        cpp2::in<std::string_view> msg
    ) const& -> void
    {
        if (!(b)) {
            error(msg);
        }
    }

    auto compiler_services::error(cpp2::in<std::string_view> msg) const& -> void
    {
        auto message {cpp2::as_<std::string>(msg)}; 
        if (!(CPP2_UFCS_0(empty, metafunction_name))) {
            message = "while applying @" + metafunction_name + " - " + message;
        }
        static_cast<void>(CPP2_UFCS(emplace_back, (*cpp2::assert_not_null(errors)), position(), std::move(message)));
    }

    compiler_services::~compiler_services() noexcept{}
compiler_services::compiler_services(compiler_services const& that)
                                : errors{ that.errors }
                                , errors_original_size{ that.errors_original_size }
                                , generated_tokens{ that.generated_tokens }
                                , parser{ that.parser }
                                , metafunction_name{ that.metafunction_name }
                                , metafunction_args{ that.metafunction_args }{}

#line 192 "reflect.h2"
    declaration_base::declaration_base(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : compiler_services{ s }
        , n{ n_ }
#line 197 "reflect.h2"
    {

#line 200 "reflect.h2"
        cpp2::Default.expects(n, "a meta::declaration must point to a valid declaration_node, not null");
    }

    [[nodiscard]] auto declaration_base::position() const& -> source_position { return CPP2_UFCS_0(position, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration_base::print() const& -> std::string { return CPP2_UFCS(pretty_print_visualize, (*cpp2::assert_not_null(n)), 0);  }

    declaration_base::~declaration_base() noexcept{}
declaration_base::declaration_base(declaration_base const& that)
                                : compiler_services{ static_cast<compiler_services const&>(that) }
                                , n{ that.n }{}

#line 216 "reflect.h2"
    declaration::declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration_base{ n_, s }
#line 221 "reflect.h2"
    {

    }

    [[nodiscard]] auto declaration::is_public() const& -> bool { return CPP2_UFCS_0(is_public, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_protected() const& -> bool { return CPP2_UFCS_0(is_protected, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_private() const& -> bool { return CPP2_UFCS_0(is_private, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_default_access() const& -> bool { return CPP2_UFCS_0(is_default_access, (*cpp2::assert_not_null(n)));  }

    auto declaration::default_to_public() & -> void { static_cast<void>(CPP2_UFCS_0(make_public, (*cpp2::assert_not_null(n)))); }
    auto declaration::default_to_protected() & -> void { static_cast<void>(CPP2_UFCS_0(make_protected, (*cpp2::assert_not_null(n))));  }
    auto declaration::default_to_private() & -> void { static_cast<void>(CPP2_UFCS_0(make_private, (*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto declaration::make_public() & -> bool { return CPP2_UFCS_0(make_public, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_protected() & -> bool { return CPP2_UFCS_0(make_protected, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_private() & -> bool { return CPP2_UFCS_0(make_private, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::has_name() const& -> bool { return CPP2_UFCS_0(has_name, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::has_name(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_name, (*cpp2::assert_not_null(n)), s); }

    [[nodiscard]] auto declaration::name() const& -> std::string_view{
        if (has_name()) {return CPP2_UFCS_0(as_string_view, (*cpp2::assert_not_null(CPP2_UFCS_0(name, *cpp2::assert_not_null(n))))); }
        else          { return ""; }
    }

    [[nodiscard]] auto declaration::has_initializer() const& -> bool { return CPP2_UFCS_0(has_initializer, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration::is_global() const& -> bool { return CPP2_UFCS_0(is_global, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_function() const& -> bool { return CPP2_UFCS_0(is_function, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_object() const& -> bool { return CPP2_UFCS_0(is_object, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_type() const& -> bool { return CPP2_UFCS_0(is_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_namespace() const& -> bool { return CPP2_UFCS_0(is_namespace, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_alias() const& -> bool { return CPP2_UFCS_0(is_alias, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::is_function_expression() const& -> bool { return CPP2_UFCS_0(is_function_expression, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration::as_function() const& -> function_declaration { return function_declaration(n, (*this));  }
    [[nodiscard]] auto declaration::as_object() const& -> object_declaration { return object_declaration(n, (*this)); }
    [[nodiscard]] auto declaration::as_type() const& -> type_declaration { return type_declaration(n, (*this)); }
    [[nodiscard]] auto declaration::as_alias() const& -> alias_declaration { return alias_declaration(n, (*this)); }

    [[nodiscard]] auto declaration::get_parent() const& -> declaration { return declaration(n, (*this)); }

    [[nodiscard]] auto declaration::parent_is_function() const& -> bool { return CPP2_UFCS_0(parent_is_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_object() const& -> bool { return CPP2_UFCS_0(parent_is_object, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_type() const& -> bool { return CPP2_UFCS_0(parent_is_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_namespace() const& -> bool { return CPP2_UFCS_0(parent_is_namespace, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_alias() const& -> bool { return CPP2_UFCS_0(parent_is_alias, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_polymorphic() const& -> bool { return CPP2_UFCS_0(parent_is_polymorphic, (*cpp2::assert_not_null(n)));  }

    declaration::~declaration() noexcept{}
declaration::declaration(declaration const& that)
                                : declaration_base{ static_cast<declaration_base const&>(that) }{}

#line 280 "reflect.h2"
    function_declaration::function_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 285 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_function, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto function_declaration::index_of_parameter_named(cpp2::in<std::string_view> s) const& -> int { return CPP2_UFCS(index_of_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_in_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_in_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_out_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_out_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_move_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_move_parameter_named, (*cpp2::assert_not_null(n)), s); }

    [[nodiscard]] auto function_declaration::has_parameter_with_name_and_pass(cpp2::in<std::string_view> s, cpp2::in<passing_style> pass) const& -> bool { 
                                                  return CPP2_UFCS(has_parameter_with_name_and_pass, (*cpp2::assert_not_null(n)), s, pass);  }
    [[nodiscard]] auto function_declaration::is_function_with_this() const& -> bool { return CPP2_UFCS_0(is_function_with_this, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_virtual() const& -> bool { return CPP2_UFCS_0(is_virtual_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_defaultable() const& -> bool { return CPP2_UFCS_0(is_defaultable_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor() const& -> bool { return CPP2_UFCS_0(is_constructor, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_default_constructor() const& -> bool { return CPP2_UFCS_0(is_default_constructor, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_move() const& -> bool { return CPP2_UFCS_0(is_move, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_swap() const& -> bool { return CPP2_UFCS_0(is_swap, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_in_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_in_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_move_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_move_that, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_assignment() const& -> bool { return CPP2_UFCS_0(is_assignment, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_in_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_in_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_move_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_move_that, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_destructor() const& -> bool { return CPP2_UFCS_0(is_destructor, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::is_copy_or_move() const& -> bool { return is_constructor_with_that() || is_assignment_with_that(); }

    [[nodiscard]] auto function_declaration::has_declared_return_type() const& -> bool { return CPP2_UFCS_0(has_declared_return_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_bool_return_type() const& -> bool { return CPP2_UFCS_0(has_bool_return_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_non_void_return_type() const& -> bool { return CPP2_UFCS_0(has_non_void_return_type, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::unnamed_return_type() const& -> std::string { return CPP2_UFCS_0(unnamed_return_type_to_string, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::is_binary_comparison_function() const& -> bool { return CPP2_UFCS_0(is_binary_comparison_function, (*cpp2::assert_not_null(n)));  }

    auto function_declaration::default_to_virtual() & -> void { static_cast<void>(CPP2_UFCS_0(make_function_virtual, (*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto function_declaration::make_virtual() & -> bool { return CPP2_UFCS_0(make_function_virtual, (*cpp2::assert_not_null(n))); }

    function_declaration::function_declaration(function_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 337 "reflect.h2"
    object_declaration::object_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 342 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_object, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto object_declaration::is_const() const& -> bool { return CPP2_UFCS_0(is_const, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto object_declaration::has_wildcard_type() const& -> bool { return CPP2_UFCS_0(has_wildcard_type, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto object_declaration::type() const& -> std::string{
        auto ret {CPP2_UFCS_0(object_type, (*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this type: " + ret);
        return ret; 
    }

    [[nodiscard]] auto object_declaration::initializer() const& -> std::string{
        auto ret {CPP2_UFCS_0(object_initializer, (*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this initializer: " + ret);
        return ret; 
    }

    object_declaration::object_declaration(object_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 373 "reflect.h2"
    type_declaration::type_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 378 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_type, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto type_declaration::is_polymorphic() const& -> bool { return CPP2_UFCS_0(is_polymorphic, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::is_final() const& -> bool { return CPP2_UFCS_0(is_type_final, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::make_final() & -> bool { return CPP2_UFCS_0(make_type_final, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto type_declaration::get_member_functions() const& -> 
        std::vector<function_declaration>
    {
        std::vector<function_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::functions) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_objects() const& -> 
        std::vector<object_declaration>
    {
        std::vector<object_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::objects) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_types() const& -> 
        std::vector<type_declaration>
    {
        std::vector<type_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::types) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_aliases() const& -> 
        std::vector<alias_declaration>
    {
        std::vector<alias_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::aliases) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_members() const& -> 
        std::vector<declaration>
    {
        std::vector<declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::all) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::query_declared_value_set_functions() const& -> query_declared_value_set_functions__ret

#line 444 "reflect.h2"
    {
            cpp2::deferred_init<bool> out_this_in_that;
            cpp2::deferred_init<bool> out_this_move_that;
            cpp2::deferred_init<bool> inout_this_in_that;
            cpp2::deferred_init<bool> inout_this_move_that;
#line 445 "reflect.h2"
        auto declared {CPP2_UFCS_0(find_declared_value_set_functions, (*cpp2::assert_not_null(n)))}; 
        out_this_in_that.construct(declared.out_this_in_that != nullptr);
        out_this_move_that.construct(declared.out_this_move_that != nullptr);
        inout_this_in_that.construct(declared.inout_this_in_that != nullptr);
        inout_this_move_that.construct(std::move(declared).inout_this_move_that != nullptr);
    return  { std::move(out_this_in_that.value()), std::move(out_this_move_that.value()), std::move(inout_this_in_that.value()), std::move(inout_this_move_that.value()) }; }

    [[nodiscard]] auto type_declaration::add_member(cpp2::in<std::string_view> source) & -> 
        bool
    {
        auto decl {parse_statement(source)}; 
        if (decl) {
            return CPP2_UFCS(add_type_member, (*cpp2::assert_not_null(n)), std::move(decl)); 
        }
        return false; 
    }

    auto type_declaration::remove_all_members() & -> void { CPP2_UFCS_0(type_remove_all_members, (*cpp2::assert_not_null(n)));  }

    auto type_declaration::disable_member_function_generation() & -> void { CPP2_UFCS_0(type_disable_member_function_generation, (*cpp2::assert_not_null(n)));  }

    type_declaration::type_declaration(type_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 475 "reflect.h2"
    alias_declaration::alias_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 480 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_alias, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto alias_declaration::is_type_alias() const& -> bool { return CPP2_UFCS_0(is_type_alias, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto alias_declaration::is_namespace_alias() const& -> bool { return CPP2_UFCS_0(is_namespace_alias, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto alias_declaration::is_object_alias() const& -> bool { return CPP2_UFCS_0(is_object_alias, (*cpp2::assert_not_null(n))); }

    alias_declaration::alias_declaration(alias_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 503 "reflect.h2"
auto add_virtual_destructor(meta::type_declaration& t) -> void
{
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "operator=: (virtual move this) = { }"), 
               "could not add virtual destructor");
}

#line 522 "reflect.h2"
auto interface(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& m : CPP2_UFCS_0(get_members, t) ) 
    {
        CPP2_UFCS(require, m, !(CPP2_UFCS_0(is_object, m)), 
                   "interfaces may not contain data objects");
        if (CPP2_UFCS_0(is_function, m)) {
            auto mf {CPP2_UFCS_0(as_function, m)}; 
            CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_copy_or_move, mf)), 
                        "interfaces may not copy or move; consider a virtual clone() instead");
            CPP2_UFCS(require, mf, !(CPP2_UFCS_0(has_initializer, mf)), 
                        "interface functions must not have a function body; remove the '=' initializer");
            CPP2_UFCS(require, mf, CPP2_UFCS_0(make_public, mf), 
                        "interface functions must be public");
            CPP2_UFCS_0(default_to_virtual, mf);
            has_dtor |= CPP2_UFCS_0(is_destructor, mf);
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS_0(add_virtual_destructor, t);
    }
}

#line 568 "reflect.h2"
auto polymorphic_base(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) 
    {
        if (CPP2_UFCS_0(is_default_access, mf)) {
            CPP2_UFCS_0(default_to_public, mf);
        }
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_copy_or_move, mf)), 
                    "polymorphic base types may not copy or move; consider a virtual clone() instead");
        if (CPP2_UFCS_0(is_destructor, mf)) {
            has_dtor = true;
            CPP2_UFCS(require, mf, (CPP2_UFCS_0(is_public, mf) && CPP2_UFCS_0(is_virtual, mf)) 
                        || (CPP2_UFCS_0(is_protected, mf) && !(CPP2_UFCS_0(is_virtual, mf))), 
                        "a polymorphic base type destructor must be public and virtual, or protected and nonvirtual");
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS_0(add_virtual_destructor, t);
    }
}

#line 613 "reflect.h2"
auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::in<std::string_view> ordering
) -> void
{
    auto has_spaceship {false}; 

    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) 
    {
        if (CPP2_UFCS(has_name, mf, "operator<=>")) {
            has_spaceship = true;
            auto return_name {CPP2_UFCS_0(unnamed_return_type, mf)}; 
            if (CPP2_UFCS(find, return_name, ordering) == return_name.npos) 
            {
                CPP2_UFCS(error, mf, "operator<=> must return std::" + cpp2::as_<std::string>(ordering));
            }
        }
    }

    if (!(std::move(has_spaceship))) {
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "operator<=>: (this, that) -> std::" + (cpp2::as_<std::string>(ordering)) + ";"), 
                   "could not add operator<=> with std::" + (cpp2::as_<std::string>(ordering)));
    }
}

#line 643 "reflect.h2"
auto ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "strong_ordering");
}

#line 651 "reflect.h2"
auto weakly_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "weak_ordering");
}

#line 659 "reflect.h2"
auto partially_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "partial_ordering");
}

#line 681 "reflect.h2"
auto copyable(meta::type_declaration& t) -> void
{
    //  If the user explicitly wrote any of the copy/move functions,
    //  they must also have written the most general one - we can't
    //  assume we can safely generate it for them since they've opted
    //  into customized semantics
    auto smfs {CPP2_UFCS_0(query_declared_value_set_functions, t)}; 
    if ( !(smfs.out_this_in_that) 
        && (
            smfs.out_this_move_that 
            || smfs.inout_this_in_that 
            || smfs.inout_this_move_that)) 

    {
        CPP2_UFCS(error, t, "this type is partially copyable/movable - when you provide any of the more-specific operator= signatures, you must also provide the one with the general signature (out this, that); alternatively, consider removing all the operator= functions and let them all be generated for you with default memberwise semantics");
    }
    else {if (!(std::move(smfs).out_this_in_that)) {
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "operator=: (out this, that) = { }"), 
                   "could not add general operator=:(out this, that)");
    }}
}

#line 710 "reflect.h2"
auto basic_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(copyable, t);

    auto has_default_ctor {false}; 
    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) {
        has_default_ctor |= CPP2_UFCS_0(is_default_constructor, mf);
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_protected, mf)) && !(CPP2_UFCS_0(is_virtual, mf)), 
                    "a value type may not have a protected or virtual function");
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_destructor, mf)) || CPP2_UFCS_0(is_public, mf), 
                    "a value type may not have a non-public destructor");
    }

    if (!(std::move(has_default_ctor))) {
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "operator=: (out this) = { }"), 
                   "could not add default constructor");
    }
}

#line 739 "reflect.h2"
auto value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

auto weakly_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(weakly_ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

auto partially_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(partially_ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

#line 783 "reflect.h2"
auto cpp2_struct(meta::type_declaration& t) -> void
{
    for ( auto& m : CPP2_UFCS_0(get_members, t) ) 
    {
        CPP2_UFCS(require, m, CPP2_UFCS_0(make_public, m), 
                   "all struct members must be public");
        if (CPP2_UFCS_0(is_function, m)) {
            auto mf {CPP2_UFCS_0(as_function, m)}; 
            CPP2_UFCS(require, t, !(CPP2_UFCS_0(is_virtual, mf)), 
                       "a struct may not have a virtual function");
            CPP2_UFCS(require, t, !(CPP2_UFCS(has_name, mf, "operator=")), 
                       "a struct may not have a user-defined operator=");
        }
    }
    CPP2_UFCS_0(disable_member_function_generation, t);
}

#line 824 "reflect.h2"
[[nodiscard]] auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::in<bool> bitwise
    ) -> basic_enum__ret

#line 833 "reflect.h2"
{
    std::string underlying_type {""};
        cpp2::deferred_init<std::string> strict_underlying_type;
#line 834 "reflect.h2"
    std::vector<value_member_info> enumerators {}; 
    cpp2::i64 min_value {0}; 
    cpp2::i64 max_value {0}; 

    //  1. Gather: The names of all the user-written members, and find/compute the type

    underlying_type = CPP2_UFCS(get_argument, t, 0);// use the first template argument, if there was one

    auto found_non_numeric {false}; 
{
std::string value = "-1";

#line 845 "reflect.h2"
    for ( 
          auto const& m : CPP2_UFCS_0(get_members, t) ) 
    {
        CPP2_UFCS(require, m, (CPP2_UFCS_0(is_public, m) || CPP2_UFCS_0(is_default_access, m)) && CPP2_UFCS_0(is_object, m), 
                   "an enumerator cannot be protected or private");

        if (CPP2_UFCS_0(is_object, m)) {
            auto mo {CPP2_UFCS_0(as_object, m)}; 
            if (!(CPP2_UFCS_0(has_wildcard_type, mo))) {
                CPP2_UFCS(error, mo, "an explicit underlying type should be specified as a template argument to the metafunction - try 'enum<u16>' or 'flag_enum<u64>'");
            }

            auto init {CPP2_UFCS_0(initializer, mo)}; 

            auto is_default_or_numeric {is_empty_or_a_decimal_number(init)}; 
            found_non_numeric |= !(CPP2_UFCS_0(empty, init)) && !(is_default_or_numeric);
            CPP2_UFCS(require, m, !(is_default_or_numeric) || !(found_non_numeric) || CPP2_UFCS(has_name, mo, "none"), 
                cpp2::to_string(CPP2_UFCS_0(name, mo)) + ": enumerators with non-numeric values must come after all default and numeric values");

            nextval(value, init);

            auto v {std::strtoll(&cpp2::assert_in_bounds(value, 0), nullptr, 10)}; // for non-numeric values we'll just get 0 which is okay for now
            if (cpp2::cmp_less(v,min_value)) {
                min_value = v;
            }
            if (cpp2::cmp_greater(v,max_value)) {
                max_value = v;
            }

            //  Adding local variable 'e' to work around a Clang warning
            value_member_info e {cpp2::as_<std::string>(CPP2_UFCS_0(name, mo)), "", value}; 
            CPP2_UFCS(push_back, enumerators, e);
        }
    }
}

    //  Compute the default underlying type, if it wasn't explicitly specified
#line 881 "reflect.h2"
    if (underlying_type == "") 
    {
        CPP2_UFCS(require, t, !(std::move(found_non_numeric)), 
            "if you write an enumerator with a non-numeric value, you must specify the underlying type");

        if (!(bitwise)) {
            if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i8>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i8>::max())) {
                underlying_type = "i8";
            }
            else {if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i16>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i16>::max())) {
                underlying_type = "i16";
            }
            else {if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i32>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i32>::max())) {
                underlying_type = "i32";
            }
            else {if (cpp2::cmp_greater_eq(std::move(min_value),std::numeric_limits<cpp2::i64>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i64>::max())) {
                underlying_type = "i64";
            }
            else {
                CPP2_UFCS(error, t, "values are outside the range representable by the largest supported underlying signed type (i64)");
            }}}}
        }
        else {
            auto umax {max_value * cpp2::as_<cpp2::u64, 2>()}; 
            if (cpp2::cmp_less_eq(umax,std::numeric_limits<cpp2::u8>::max())) {
                underlying_type = "u8";
            }
            else {if (cpp2::cmp_less_eq(umax,std::numeric_limits<cpp2::u16>::max())) {
                underlying_type = "u16";
            }
            else {if (cpp2::cmp_less_eq(std::move(umax),std::numeric_limits<cpp2::u32>::max())) {
                underlying_type = "u32";
            }
            else {
                underlying_type = "u64";
            }}}
        }
    }

    strict_underlying_type.construct("cpp2::strict_value<" + cpp2::to_string(underlying_type) + "," + cpp2::to_string(CPP2_UFCS_0(name, t)) + "," + cpp2::to_string(bitwise) + ">");

#line 923 "reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents

    CPP2_UFCS_0(remove_all_members, t);

    //  Add the base value and a constructor
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    this: " + cpp2::to_string(strict_underlying_type.value()) + " = ();"), 
                "could not add enumeration base value");

    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    operator=: (implicit out this, value: " + cpp2::to_string(strict_underlying_type.value()) + ") = { " + cpp2::to_string(strict_underlying_type.value()) + " = value; }"), 
                "could not add enumeration constructor");

    //  Add the enumerators
    for ( auto const& e : enumerators ) {
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public " + cpp2::to_string(e.name) + " :== " + cpp2::to_string(strict_underlying_type.value()) + "( " + cpp2::to_string(e.value) + " );"), 
                   "could not add enumerator" + e.name);
    }

    //  Provide a 'size' function to count the number of enumerators
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    size: () -> _ = " + cpp2::to_string(CPP2_UFCS_0(ssize, enumerators)) + ";"), 
               "could not add size");
{
std::string to_string = "    to_string: (value: " + cpp2::to_string(strict_underlying_type.value()) + ") -> std::string = { \n";

    //  Provide a 'to_string' function to print enumerator name(s)

#line 946 "reflect.h2"
    {
        to_string += "    ret: std::string = ();\n";

        if (bitwise) {
            to_string += "    comma: std::string = ();\n";
        }
{
auto first = true;

#line 954 "reflect.h2"
        for ( 

              auto const& e : enumerators )  { do {
            if (e.name != "_") {// ignore unnamed values
                if (bitwise) {
                    if (first) {
                        to_string += "    ret = \"(\";\n";
                    }
                    if (e.name == "none") { // a "none" flag should match if no bits set
                        to_string += "    if value == " + cpp2::to_string(e.name) + " { ret += comma + \"" + cpp2::to_string(e.name) + "\"; comma = \", \"; }\n";
                    }
                    else {                  // other flags need to be &-ed
                        to_string += "    if (value & " + cpp2::to_string(e.name) + ") == " + cpp2::to_string(e.name) + " { ret += comma + \"" + cpp2::to_string(e.name) + "\"; comma = \", \"; }\n";
                    }
                }
                else {
                    to_string += "if value == " + cpp2::to_string(e.name) + " { ret = \"" + cpp2::to_string(e.name) + "\"; }\n";
                }
            }
        } while (false); first = false; }
}

#line 975 "reflect.h2"
        to_string += "    if ret.empty() { ret = \"(invalid " + cpp2::to_string(CPP2_UFCS_0(name, t)) + " enumerator value)\"; }\n";

        if (bitwise) {
            to_string += "    return ret+\")\";\n}\n";
        }
        else {
            to_string += "    return ret;\n}\n";
        }

        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, std::move(to_string)), 
                   "could not add to_string static function");
    }
}

#line 988 "reflect.h2"
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    to_string: (this) -> std::string = { return " + cpp2::to_string(CPP2_UFCS_0(name, t)) + "::to_string(this); }"), 
               "could not add to_string member function");

#line 992 "reflect.h2"
    //  3. A basic_enum is-a value type

    CPP2_UFCS_0(basic_value, t);
return  { std::move(underlying_type), std::move(strict_underlying_type.value()) }; }

#line 1007 "reflect.h2"
auto cpp2_enum(meta::type_declaration& t) -> void
{
    //  Let basic_enum do its thing, with an incrementing value generator
    static_cast<void>(CPP2_UFCS(basic_enum, t, 
        [](std::string& value, cpp2::in<std::string> specified_value) -> void{
            if (!(CPP2_UFCS_0(empty, specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&cpp2::assert_in_bounds(value, 0), nullptr, 10)}; 
                value = cpp2::as_<std::string>((std::move(v) + 1));
            }
        }, 
        false   // disable bitwise operations
    ));
}

#line 1034 "reflect.h2"
auto flag_enum(meta::type_declaration& t) -> void
{
    //  Add "none" member as a regular name to signify "no flags set"
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "none := 0;"), 
                "could not add 'none' enumerator");

    //  Let basic_enum do its thing, with a power-of-two value generator
    static_cast<void>(CPP2_UFCS(basic_enum, t, 
        [](std::string& value, cpp2::in<std::string> specified_value) -> void{
            if (!(CPP2_UFCS_0(empty, specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&cpp2::assert_in_bounds(value, 0), nullptr, 10)}; 
                if (cpp2::cmp_less(v,1)) {
                    value = "1";
                }
                else {
                    value = cpp2::as_<std::string>((std::move(v) * 2));
                }
            }
        }, 
        true    // enable bitwise operations
    ));
}

#line 1084 "reflect.h2"
auto cpp2_union(meta::type_declaration& t) -> void
{
    std::vector<value_member_info> alternatives {}; 
{
auto value = 0;

    //  1. Gather: All the user-written members, and find/compute the max size

#line 1091 "reflect.h2"
    for ( 

          auto const& m : CPP2_UFCS_0(get_members, t) )  { do 
    {
        CPP2_UFCS(require, m, (CPP2_UFCS_0(is_public, m) || CPP2_UFCS_0(is_default_access, m)) && CPP2_UFCS_0(is_object, m), 
                   "a union alternative cannot be protected or private");

        if (CPP2_UFCS_0(is_object, m)) {
            auto mo {CPP2_UFCS_0(as_object, m)}; 
            CPP2_UFCS(require, mo, CPP2_UFCS_0(empty, CPP2_UFCS_0(initializer, mo)), 
                        "a union alternative cannot have an initializer");

            //  Adding local variable 'e' to work around a Clang warning
            value_member_info e {cpp2::as_<std::string>(CPP2_UFCS_0(name, mo)), CPP2_UFCS_0(type, mo), cpp2::as_<std::string>(value)}; 
            CPP2_UFCS(push_back, alternatives, e);
        }
    } while (false); ++value; }
}

#line 1109 "reflect.h2"
    std::string discriminator_type {}; 
    if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i8>::max())) {
        discriminator_type = "i8";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i16>::max())) {
        discriminator_type = "i16";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i32>::max())) {
        discriminator_type = "i32";
    }
    else {
        discriminator_type = "i64";
    }}}

#line 1124 "reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents

    CPP2_UFCS_0(remove_all_members, t);
{
std::string storage = "    storage__: std::array<std::byte, cpp2::max( ";

    //  Provide storage

#line 1130 "reflect.h2"
    {
{
std::string comma = "";

#line 1133 "reflect.h2"
        for ( 

              auto const& e : alternatives )  { do {
            storage += comma + "sizeof(" + cpp2::to_string(e.type) + ")";
        } while (false); comma = ", "; }
}

#line 1139 "reflect.h2"
        storage += " )> = ();\n";
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, std::move(storage)), 
                   "could not add storage");
    }
}

    //  Provide discriminator
#line 1145 "reflect.h2"
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    discriminator__: " + cpp2::to_string(std::move(discriminator_type)) + " = -1;\n"), 
               "could not add discriminator");

    //  Add the alternatives: is_alternative, get_alternative, and set_alternative
    for ( 
         auto const& a : alternatives ) 
    {
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public is_" + cpp2::to_string(a.name) + ": (this) -> bool = discriminator__ == " + cpp2::to_string(a.value) + ";\n"), 
                   "could not add is_" + a.name);

        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public get_" + cpp2::to_string(a.name) + ": (this) -> forward _ [[pre: is_" + cpp2::to_string(a.name) + "()]] = reinterpret_cast<* const " + cpp2::to_string(a.type) + ">(storage__&)*;\n"), 
                   "could not add get_" + a.name);

        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public get_" + cpp2::to_string(a.name) + ": (inout this) -> forward _ [[pre: is_" + cpp2::to_string(a.name) + "()]] = reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&)*;\n"), 
                   "could not add get_" + a.name);

        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public set_" + cpp2::to_string(a.name) + ": (inout this, value: " + cpp2::to_string(a.type) + ") = { if !is_" + cpp2::to_string(a.name) + "() { destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&), value); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&)* = value; } discriminator__ = " + cpp2::to_string(a.value) + "; }\n"), 
                   "could not add set_" + a.name);

        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    public set_" + cpp2::to_string(a.name) + ": (inout this, forward args...: _) = { if !is_" + cpp2::to_string(a.name) + "() { destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&), args...); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&)* = :" + cpp2::to_string(a.type) + " = (args...); } discriminator__ = " + cpp2::to_string(a.value) + "; }\n"), 
                   "could not add variadic set_" + a.name);
    }
{
std::string destroy = "    private destroy: (inout this) = {\n";

    ////  Add operator<<
    //(stream: std::string = "    operator<<: (inout o: std::ostream, that) -> forward std::ostream = {\n")
    //{
    //    (first := true)
    //    for  alternatives 
    //    next first = false  
    //    do   (a) {
    //        stream += "if discriminator__ == (a.value)$ { o << reinterpret_cast<*(a.type)$>(storage__&)*; }\n";
    //    }

    //    stream += "    return o;\n}\n";
    //    t.require( t.add_member( stream ),
    //               "could not add operator<<");
    //}

    //  Add destroy

#line 1185 "reflect.h2"
    {
        for ( 
              auto const& a : alternatives ) {
            destroy += "if discriminator__ == " + cpp2::to_string(a.value) + " { std::destroy_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(storage__&) ); }\n";
        }

        destroy += "}\n";
        CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, std::move(destroy)), 
                   "could not add destroy");
    }
}

    //  Add the destructor
#line 1197 "reflect.h2"
    CPP2_UFCS(require, t, CPP2_UFCS(add_member, t, "    operator=: (move this) = { destroy(); } "), 
               "could not add destructor");
}

#line 1206 "reflect.h2"
auto print(cpp2::in<meta::type_declaration> t) -> void
{
    std::cout << CPP2_UFCS_0(print, t) << "\n";
}

#line 1214 "reflect.h2"
}
}

#endif
