#include "byte_stream.hh"
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) : _byte_stream(1)
{
    // DUMMY_CODE(capacity);
    _capacity = capacity;
    _bytes_read = 0;
    _bytes_written = 0;
    _end = false;
    _error = false;
    cout << _byte_stream.size()<<endl;
    _byte_stream.push_front('a');
    cout << _byte_stream.size() << endl;
    cout << _byte_stream.at(0) << endl;
    cout << _byte_stream.at(1) << endl;
}

int main(){
    ByteStream a(1);
}
// size_t ByteStream::write(const string &data)
// {
//     DUMMY_CODE(data);
//     return {};
// }

// //! \param[in] len bytes will be copied from the output side of the buffer
// string ByteStream::peek_output(const size_t len) const
// {
//     DUMMY_CODE(len);
//     return {};
// }

// //! \param[in] len bytes will be removed from the output side of the buffer
// void ByteStream::pop_output(const size_t len) { DUMMY_CODE(len); }

// //! Read (i.e., copy and then pop) the next "len" bytes of the stream
// //! \param[in] len bytes will be popped and returned
// //! \returns a string
// std::string ByteStream::read(const size_t len)
// {
//     DUMMY_CODE(len);
//     return {};
// }

// void ByteStream::end_input() {}

// bool ByteStream::input_ended() const { return {}; }

// size_t ByteStream::buffer_size() const { return {}; }

// bool ByteStream::buffer_empty() const { return {}; }

// bool ByteStream::eof() const { return false; }

// size_t ByteStream::bytes_written() const { return {}; }

// size_t ByteStream::bytes_read() const { return {}; }

// size_t ByteStream::remaining_capacity() const { return {}; }