
void do_something_exceptional();

template<typename T>
void log( T const& );


class BaseException {};
class DerivedException: public BaseException {};





void exceptionally_buggy() {
    try {
        do_something_exceptional();
    }
    catch ( BaseException const& e ) {
        log( e );
    }
    catch( int i ) {
        log( i );
    }
    catch ( DerivedException const& e ) {
        log( e );
    }
}
