package it.sevenbits;

import it.sevenbits.formatter.FormatterException;
import it.sevenbits.lexer.ILexer;
import it.sevenbits.lexer.Lexer;
import it.sevenbits.lexer.IToken;
import it.sevenbits.lexer.Token;
import it.sevenbits.lexer.LexerException;
import it.sevenbits.reader.IReader;
import it.sevenbits.reader.ReaderException;
import it.sevenbits.reader.StringReader;

import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.Assert.*;
import static org.mockito.Mockito.*;


public class LexerTest {
    private boolean equalsArr(ArrayList<IToken> arr1, ArrayList<IToken> arr2) {
        if (arr1.size() != arr2.size()) {
            return false;
        }
        for (int i = 0; i < arr1.size(); i++) {
            if (!arr1.get(i).getLexeme().equals(arr2.get(i).getLexeme()) ||
                    !arr1.get(i).getType().equals(arr2.get(i).getType())) {
                return false;
            }
        }
        return true;
    }

    @org.junit.Test
    public void validCode() throws FormatterException {
        String example = "aaa {bbb;ccc;}";
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        ArrayList<IToken> expected = new ArrayList<>(Arrays.asList(new Token("aaa", "word"),
                new Token("{", "special"), new Token("bbb", "word"), new Token(";", "special"),
                new Token("ccc", "word"), new Token(";", "special"), new Token("}", "special")));
        ArrayList<IToken> actual = new ArrayList<>();
        while (lexer.hasMoreTokens()) {
            try {
                actual.add(lexer.readToken());
            } catch (LexerException e) {
                e.printStackTrace();
            }
        }

        assertTrue(equalsArr(expected, actual));
    }

    @org.junit.Test
    public void CCode() throws FormatterException {
        String example = "while ( count <= 100) { count++; if(count== 25){   count*=2;}}";
        StringReader reader = new StringReader(example);
        ILexer lexer = new Lexer(reader);

        ArrayList<IToken> expected = new ArrayList<>(Arrays.asList(new Token("while", "word"),
                new Token("(", "special"), new Token("count", "word"), new Token("<=", "special"),
                new Token("100", "word"), new Token(")", "special"), new Token("{", "special"),
                new Token("count", "word"), new Token("++", "special"), new Token(";", "special"),
                new Token("if", "word"), new Token("(", "special"), new Token("count", "word"),
                new Token("==", "special"), new Token("25", "word"), new Token(")", "special"),
                new Token("{", "special"), new Token("count", "word"), new Token("*=", "special"),
                new Token("2", "word"), new Token(";", "special"), new Token("}", "special"), new Token("}", "special")));
        ArrayList<IToken> actual = new ArrayList<>();
        while (lexer.hasMoreTokens()) {
            try {
                actual.add(lexer.readToken());
            } catch (LexerException e) {
                e.printStackTrace();
            }
        }

        assertTrue(equalsArr(expected, actual));
    }

    @org.junit.Test()
    public void LexerWithoutReader() throws LexerException, ReaderException {
        IReader mockReader = mock(IReader.class);
        when(mockReader.hasNext()).thenReturn(true, true, true, true, true, true, true, true, true, true, true, true, true, false);
        when(mockReader.read()).thenReturn('a', 'a', 'a', '{', 'b', 'b', 'b', ';', 'c', 'c', 'c', ';','}');
        ILexer lexer = new Lexer(mockReader);

        ArrayList<IToken> expected = new ArrayList<>(Arrays.asList(new Token("aaa", "word"), new Token("{", "special"),
                new Token("bbb", "word"), new Token(";", "special"), new Token("ccc", "word"),
                new Token(";", "special"), new Token("}", "special")));
        ArrayList<IToken> actual = new ArrayList<IToken>();
        while (lexer.hasMoreTokens()) {
            actual.add(lexer.readToken());
        }

        assertTrue(equalsArr(expected, actual));
    }
}
