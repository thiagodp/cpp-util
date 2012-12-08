/****************************************************************************
 *                                                                          *
 *      Biblioteca de codigo C++                                            *
 *                                                                          *
 *      Copyright (c), 2008 - Thiago Delgado Pinto (thiago-dp@bol.com.br)   *
 *      http://devhints.blogspot.com/                                       *
 *									                                        *
 *      Distribuído sob a licença Creative Commons versão 3                 *
 *      http://www.creativecommons.org.br/                                  *
 *                                                                          *
 ****************************************************************************/

//---------------------------------------------------------------------------
#ifndef uStrUtilH
#define uStrUtilH
//---------------------------------------------------------------------------

// C++ ANSI
#include <string>
#include <sstream>
#include <strstream>
#include <algorithm>
#include <limits>

/**
 * StrUtil contem funcoes relacionadas 'a manipulacao de strings C++ ANSI/ISO.
 *
 * @author	Thiago Delgado Pinto
 */

namespace StrUtil
{
	using std::string;
	using std::ostringstream;
	using std::istrstream;
	using std::transform;


	/**
	 * ToString converte um tipo de dado simples em uma string.
	 * Se o tipo nao puder ser convertido, o endereco da variavel passada
	 * sera' resultado na conversao.
	 *
	 * @param T		Tipo de dado a ser assumido para conversao.
	 *			E' opcional pois o compilador assume
	 *			automaticamente.
	 * @param arg		Valor a ser convertido.
	 * @param precision	Numero de digitos apos a casa decimal (opcional)
	 * @return		String convertida a partir do valor.
	 *
	 * EXEMPLOS DE USO:
	 *
	 *	double d = 9.234f;
	 *	string sd = ToString( d, 3 );
	 *
	 *	int i = 3000;
	 *	string si = ToString( i );
	 *
	 *	OU DEFININDO EXPLICITAMENTE O TIPO:
	 *
	 *	int j = 2000;
	 *	string sj = ToString< int >( j );
	 *
	 * OBSERVACOES:
	 *
	 *	O maior tipo numerico suportado e' long double.
	 *	Para saber qual a precisão no seu compilador, veja a classe
	 *	numeric_limits (da limits.h). Exemplo:
	 *
	 *	cout << numeric_limits< double >::digits10 << endl;
	 *	cout << numeric_limits< long double >::digits10 << endl;
	 *
	 *	CASO A PRECISAO NAO SEJA ESPECIFICADA, E' ESTABELECIDA
	 *	A PRECISAO NUMERICA MAXIMA PARA O CAMPO.
	 */

	template < typename T >
	string ToString(const T &arg, const size_t &precision = 0)
	{
		ostringstream out;
		out.flags( ios_base::fixed );

		if ( precision > 0 )
		{
			out.precision( precision );
		}
		else
		{
			out.precision( numeric_limits< T >::digits10 );
		}

		out << arg;

		return ( out.str() );
	};


	/**
	 * FromString converte uma string em um valor do tipo de dados
	 * especificado.
	 *
	 * @param T	Tipo de dados desejado para conversao.
	 * @param arg	String a ser convertida no tipo de dados desejado.
	 * @return	Valor da string no tipo de dados parametrizado.
	 *
	 * EXEMPLOS DE USO:
	 *
	 *	string sd = "9.234";
	 *	double d = FromString< double >( sd );
	 *
	 *	string si = "3000";
	 *	int i = FromString< int >( si );
	 */

	template< typename T >
	T FromString(const string &arg)
	{
		istrstream iss( arg.c_str() );

		T x;
		iss >> x;

		return ( x );
	};

	/**
	 * CharToUpper converte um caractere para maiusculo seguindo as normas
	 * da Windows-1250, Windows-1252, ISO-8859-1 e ISO-8859-2.
	 *
	 * @param ch	Caractere a ser convertido
	 * @return	Caractere convertido em maiusculo
	 */

	inline unsigned char CharToUpper(const unsigned char &ch)
	{
		unsigned char c = ch;

		if ( c && 128 )
		{
			if ( c >= 224 )
			{
				c -= 32;
				return ( c );
			}
		}

		c = std::toupper( c );
		return ( c );
	};

	/**
	 * CharToLower converte um caractere para minusculo seguindo as normas
	 * da Windows-1250, Windows-1252, ISO-8859-1 e ISO-8859-2.
	 *
	 * @param ch	Caractere a ser convertido
	 * @return	Caractere convertido em minusculo
	 */
	inline unsigned char CharToLower(const unsigned char &ch)
	{
		unsigned char c = ch;

		if ( c && 128 )
		{
			if ( ( c >= 192 ) && ( c <= 223 ) )
			{
				c += 32;
				return ( c );
			}
		}

		c = std::tolower( c );
		return ( c );
	};


	/**
	 * UpperCharTransform e' uma classe auxiliadora de transformacao de
	 * caracteres em maiusculo. E' usada basicamente pelo algoritmo
	 * std::transform.
	 */
	struct UpperCharTransform
	{
		unsigned char operator ()(const unsigned char &ch)
		{
			return ( CharToUpper( ch ) );
		}
	};

	/**
	 * LowerCharTransform e' uma classe auxiliadora de transformacao de
	 * caracteres em minusculo. E' usada basicamente pelo algoritmo
	 * std::transform.
	 */
	struct LowerCharTransform
	{
		unsigned char operator ()(const unsigned char &ch)
		{
			return ( CharToLower( ch ) );
		}
	};


	/**
	 * ToUpperCase converte uma string para maiusculo, seguindo as normas
	 * definidas pela funcao CharToUpper.
	 *
	 * @param str	String a ser convertida
	 * @return	String em maiusculo
	 */
	string ToUpperCase(const string &str)
	{
		string s( str );

		transform( s.begin(), s.end(), s.begin(), UpperCharTransform() );

		return ( s );
	};

	/**
	 * ToLowerCase converte uma string para minusculo, seguindo as normas
	 * definidas pela funcao CharToLower.
	 *
	 * @param str	String a ser convertida
	 * @return	String em minusculo
	 */
	string ToLowerCase(const string &str)
	{
		string s( str );

		transform( s.begin(), s.end(), s.begin(), LowerCharTransform() );

		return ( s );
	};


	/**
	 * ToHexString converte uma string em números hexadecimais de dois
	 * bytes equivalentes à cada caractere da string.
	 *
	 * @param str		String a ser convertida
	 * @param separator	Separador entre cada caractere (opcional)
	 * @return		String em hexadecimal
	 */
	string ToHexString(const string &str, const string &separator = "")
	{
		std::ostringstream oss;

		const size_t STR_LENGTH = str.length();

		for (size_t i = 0; ( i < STR_LENGTH ); i++)
		{
			oss << std::uppercase << std::hex << (int) str[ i ];
			oss << separator;
		}

		return ( oss.str() );
	}

}; // namespace

//---------------------------------------------------------------------------
#endif