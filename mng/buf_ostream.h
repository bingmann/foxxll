#ifndef BUF_OSTREAM_HEADER
#define BUF_OSTREAM_HEADER

/***************************************************************************
 *            buf_ostream.h
 *
 *  Tue Dec 31 17:16:10 2002
 *  Copyright  2002  Roman Dementiev
 *  dementiev@mpi-sb.mpg.de
 ****************************************************************************/


#include "../mng/buf_writer.h"

__STXXL_BEGIN_NAMESPACE

//! \brief Buffered output stream
//!
//! Writes data records to the stream of blocks.
//! \remark Writing performed in the background, i.e. with overlapping of I/O and computation
template <typename BlkTp_,typename BIDIteratorTp_>
class buf_ostream
{
	typedef BlkTp_ block_type;
	typedef BIDIteratorTp_ bid_iterator_type;
	
protected:
	buffered_writer<block_type> writer;
	bid_iterator_type current_bid;
	int current_elem;
	block_type * current_blk;
public:
	typedef typename block_type::const_reference const_reference;
	typedef typename block_type::reference reference;
	typedef buf_ostream<block_type,bid_iterator_type> _Self;
		
	//! \brief Constructs output stream object
	//! \param first_bid \c bid_iterator pointing to the first block of the stream
	//! \param nbuffers number of buffers for internal use
	buf_ostream(bid_iterator_type first_bid,int nbuffers):
		writer(nbuffers,nbuffers/2),current_bid(first_bid),
		current_elem(0)
	{
		current_blk = writer.get_free_block();
	}
	
	//! \brief Output stream operator, writes out \c record
	//! \param record const reference to block record type, containing a value of record to write to the stream
	//! \return reference to itself (stream onject)
	_Self & operator << (const_reference record)
	{
		current_blk->elem[current_elem++] = record;
		if(current_elem >= block_type::size)
		{
			current_elem = 0;
			current_blk = writer.write(current_blk,*(current_bid++));
		}
		return (*this);
	}
	
	//! \brief Returns reference to the current record
	//! \return reference to the current record
	reference current()
	{
		return current_blk->elem[current_elem];
	}
	
	//! \brief Moves to the next record in the stream
	//! \return reference to itself after the advance
	_Self & operator ++ (int)
	{
		current_elem++;
		if(current_elem >= block_type::size)
		{
			current_elem = 0;
			current_blk = writer.write(current_blk,*(current_bid++));
		}
		return (*this);
	}
	
	//! \brief Deallocates internal objects
	virtual ~buf_ostream()
	{
		assert(current_elem == 0);
	}
};

__STXXL_END_NAMESPACE

#endif