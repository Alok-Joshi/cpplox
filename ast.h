#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "token.h"
#include "environment.h"
#include <any>

namespace ast {

    class semantic_analyser;



    class expression {
        public:
        tok::token_type expression_type; //STRING, NUMBER
        friend class semantic_analyser;
        virtual void print_expression() = 0; //pure virtual function
        virtual std::any evaluate() = 0;
    };

    class statement {

        public:
        friend class semantic_analyser;
        virtual std::any execute() = 0;

    };
    class conditional_statement: public statement{
            
          expression *expr;
          statement* if_statements;
          statement *else_statements;
          public:
          std::any execute();
          conditional_statement(expression *expr, statement*  if_statements, statement *else_statements);
          friend class semantic_analyser;

    };
    class block_statement: public statement{
            
          std::vector<statement*> statements;
          public:
          std::any execute();
          block_statement(std:: vector<statement*> &statements);
          friend class semantic_analyser;
    };
    class while_statement: public statement{

        expression *expr;
        statement *statements;
        public:
        std::any execute();
        while_statement(expression *expr, statement *statements);
        friend class semantic_analyser;

    };
    class for_statement: public statement{

        statement * part1; //the declaration or assignment statement
        expression * part2; //the expression which is checked for truth value;
        expression * part3; //the operation done after every iteration of the loop
        statement * statements;
        public:
        std::any execute();
        for_statement(statement *part1, expression *part2, expression* part3,statement* statements);
        friend class semantic_analyser;

    };


    class expression_statement: public statement{

          expression *exp;
          public:
          expression_statement(expression *exp);
          std::any execute();
          friend class semantic_analyser;

    };
    class declaration_statement: public statement{

          public:
          expression *exp;
          tok:: token variable_name;
          tok:: token_type variable_type;
          declaration_statement(expression *exp,tok::token variable,tok::token_type variable_type);
          std::any execute();
          friend class semantic_analyser;

    };
    class print_statement: public statement{
        
          expression *exp;
          public:
          print_statement(expression *exp);
          std::any execute();
          friend class semantic_analyser;

    };
    class input_statement: public statement {

         tok::token input_reciever_variable;
         tok::token_type input_type;
         public:
         input_statement(tok::token input_reciever_variable,tok::token_type input_type);
         std:: any execute();

         friend class semantic_analyser;

    };

    class return_statement: public statement{

          expression *return_exp;
          public:
          return_statement(expression *return_exp);
          std::any execute();
          friend class semantic_analyser;


    };

    class function_declaration_statement: public statement{
        
          tok:: token function_name;
          tok:: token_type return_type;
          std:: vector<std:: pair<tok::token,tok::token_type>> parameters;
          statement* block;
          public:
          function_declaration_statement(tok::token function_name, std:: vector<std:: pair<tok::token,tok::token_type>> &parameters, statement* block,tok::token_type return_type);
          std:: any execute();
          friend class semantic_analyser;

    };



    class binary_expression : public expression{
        protected:
        expression * left;
        tok::token optr;
        expression *right;
        public: 
        binary_expression(expression *left, tok::token &optr, expression *right);
        void print_expression();
        std::any evaluate();
        friend class semantic_analyser;
        
    };

    class logical_expression : public binary_expression{
        public: 
        logical_expression(expression *left, tok::token &optr, expression *right);
        void print_expression();
        std::any evaluate();
        friend class semantic_analyser;
        
    };

;

    class unary_expression : public expression{
        tok::token optr;
        expression * right;

        public: 
        unary_expression(tok::token &optr, expression *right);
        void print_expression();
        std::any evaluate();
        friend class semantic_analyser;
        
    };

    class literal_expression : public expression{
        tok::token literal;
        
        public: 
        literal_expression(tok:: token &literal);
        void print_expression();
        std::any evaluate();
        friend class semantic_analyser;
    };

    class variable_literal_expression: public expression{
        
        tok::token variable_name;
        public: 
        variable_literal_expression(tok:: token &variable_name);
        tok:: token get_variable_name();
        void print_expression();
        std::any evaluate();
        friend class semantic_analyser;
    };

    class function_call_expression: public expression {
        //the flow of evaluate:
        // 1) Evaluate function_identifier_expression
        // 2) Now access the environment and get the corresponding callable object 
        // 3) call the call() function of the callable object which will return the any value

        tok::token function_name;
        std::vector<expression*> arguments;
        public:
        function_call_expression(tok::token function_name, std::vector<expression*> &arguments);
        void print_expression();
        std:: any evaluate();
        friend class semantic_analyser;

    };

    class group_expression : public expression{
        expression*  exp;
        
        public: 
        group_expression(expression* exp);
        void print_expression();
        std::any evaluate();
    };

    class class_declaration_statement: public statement {
        tok:: token variable_name;
        std::vector<statement*> methods;
        public:
        class_declaration_statement(tok:: token variable_name, std:: vector<statement*> methods);
        std:: any execute();
        
        

    };

    class semantic_analyser {

                
        std::vector<ast:: statement*> ast;
        symbol_table* symtab;
        bool analyse_statement(ast:: statement* ast);
        std::pair<bool,tok::token_type> analyse_expression(ast::expression* exp);
        bool block_resolver(ast::block_statement* block);
        bool return_encountered;

        public:
        std:: vector<std::string> error_stack;
        semantic_analyser(std:: vector<ast:: statement*> ast);
        bool analyse_program();

         

    };






}


#endif
