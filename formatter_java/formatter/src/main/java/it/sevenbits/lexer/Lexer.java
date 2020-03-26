package it.sevenbits.lexer;

import it.sevenbits.reader.IReader;
import it.sevenbits.reader.ReaderException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;

/**
 * The type Lexer.
 */
public class Lexer implements ILexer {
    private ArrayList<IToken> tokens;
    private int currToken;

    private static final HashSet<String> SPECIALSTRINGS = new HashSet<>(Arrays.asList(
            "\n", "\t", "\b", "\r", "\f", "\"", "\\", "'", "(",
            ")", "[", "]", "?", ";", "{", "}", ":", ",", ".", "@", "=",

            "+=", "-=", "/=", "*=", "%=", "«=", "»=", "&=", "^=", "|=",
            "=", "+=", "-=", "/=", "*=", "%=", "«=", "»=", "&=", "^=", "|=",
            "&&", "||", "!", "&", "|", "^", "~", "«", "»", "»>", "!=", "==",
            "<", "<=", ">", ">=", "+", "-", "*", "/", "%", "++", "--"
    ));

    /**
     * Instantiates a new Lexer.
     *
     * @param reader the reader
     */
    public Lexer(final IReader reader) {
        tokens = new ArrayList<>();
        currToken = 0;
        setTokens(reader);
    }

    private void setTokens(final IReader reader) {
        char symbol = ' ';
        boolean isSpecSymb = false;
        StringBuilder sb = new StringBuilder();
        while (reader.hasNext()) {
            try {
                symbol = reader.read();
            } catch (ReaderException e) {
                e.printStackTrace();
            }

            if (symbol != ' ' && !SPECIALSTRINGS.contains(Character.toString(symbol))) {
                if (isSpecSymb) {
                    tokens.add(newToken(sb.toString(), "special"));
                    sb.setLength(0);
                    isSpecSymb = false;
                }
                sb.append(symbol);
            } else if (SPECIALSTRINGS.contains(Character.toString(symbol))) {
                if (!isSpecSymb && sb.length() > 0) {
                    tokens.add(newToken(sb.toString(), "word"));
                    sb.setLength(0);
                }

                String tempString = sb.toString();

                sb.append(symbol);
                if (!SPECIALSTRINGS.contains(sb.toString())) {
                    if (tempString.length() > 0) {
                        tokens.add(newToken(tempString, "special"));
                    }
                    sb.setLength(0);
                    sb.append(symbol);
                }
                isSpecSymb = true;
            }

            if (symbol == ' ' && sb.length() > 0 && !SPECIALSTRINGS.contains(sb.toString())) {
                tokens.add(newToken(sb.toString(), "word"));
                sb.setLength(0);
            }
        }

        if (sb.length() > 0) {
            tokens.add(newToken(sb.toString(), "special"));
        }
    }

    /**
     * New token token.
     *
     * @param lexeme the lexeme
     * @param type   the type
     * @return the token
     */
    public IToken newToken(final String lexeme, final String type) {
        return new Token(lexeme, type);
    }

    @Override
    public boolean hasMoreTokens() {
        return currToken < tokens.size();
    }

    @Override
    public IToken readToken() throws LexerException {
        if (hasMoreTokens()) {
            return tokens.get(currToken++);
        }
        throw new LexerException("has no tokens");
    }
}
