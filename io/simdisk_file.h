#ifndef SIMDISK_HEADER
#define SIMDISK_HEADER

/***************************************************************************
 *            simdisk_file.h
 *
 *  Sat Aug 24 23:55:03 2002
 *  Copyright  2002  Roman Dementiev
 *  dementiev@mpi-sb.mpg.de
 ****************************************************************************/


#include "ufs_file.h"
#include <math.h>

namespace stxxl
{

	#define AVERAGE_SPEED (15*1024*1024)	
		
	class DiskGeometry
	{
		struct Zone
		{
			// manufactuted data
			//    int last_cyl;
			//    int sect_per_track;
			// derived data
			int first_sector;
			int sectors;
			double sustained_data_rate;	// in Mb/s
			  Zone (int
				_first_sector):first_sector (_first_sector)
			{
			};	// constructor for zone search

			  Zone (	//int _last_cyl, 
				       //int _sect_per_track,
				       int _first_sector,
				       int _sectors, double _rate):
				//last_cyl(_last_cyl),
				//       sect_per_track(_sect_per_track) ,
			 
				first_sector (_first_sector),
				sectors (_sectors),
				sustained_data_rate (_rate)
			{
			};
		};
		struct ZoneCmp
		{
			bool operator  () (const Zone & a, const Zone & b) const
			{
				return a.first_sector < b.first_sector;
			};
		};

	      protected:
		int nsurfaces;
		int bytes_per_sector;
		double cmd_ovh;	// in s
		double seek_time;	// in s
		double rot_latency;	// in s
		double head_switch_time;	// in s
		double cyl_switch_time;	// in s
		double revolution_time;	// in s
		double interface_speed;	// in byte/s
		std::set < Zone, ZoneCmp > zones;

		void add_zone (int &first_cyl, int last_cyl,
			       int sec_per_track, int &first_sect)
		{
			double rate =
				nsurfaces * sec_per_track * bytes_per_sector /
				((nsurfaces - 1) * head_switch_time +
				 cyl_switch_time +
				 nsurfaces * revolution_time);
			int sectors =
				(last_cyl - first_cyl +
				 1) * nsurfaces * sec_per_track;
			zones.insert (Zone (first_sect, sectors, rate));
			first_sect += sectors;
			first_cyl = last_cyl + 1;
		};
	      public:
		DiskGeometry ()
		{
		};
		double get_delay (off_t offset, size_t size)	// returns delay in s
		{
			/*
			  
			int first_sect = offset / bytes_per_sector;
			int last_sect = (offset + size) / bytes_per_sector;
			int sectors = size / bytes_per_sector;
			double delay =
				cmd_ovh + seek_time + rot_latency +
				double (bytes_per_sector) /
				double (interface_speed);
			
			std::set < Zone, ZoneCmp >::iterator zone =
				zones.lower_bound (first_sect);
			// cout << __PRETTY_FUNCTION__ << " " << (*zone).first_sector << endl;
			while (1)
			{
				int from_this_zone =
					last_sect - ((*zone).first_sector +
						     (*zone).sectors);
				if (from_this_zone <= 0)
				{
					delay += sectors * bytes_per_sector /
						((*zone).sustained_data_rate);
					break;
				}
				else
				{
					delay += from_this_zone *
						bytes_per_sector /
						((*zone).sustained_data_rate);
					zone++;
					stxxl_nassert (zone == zones.end ());
					sectors -= from_this_zone;
				}
			}  

			return delay;
			
			*/
			return 	double(size)/double(AVERAGE_SPEED);
		};
		~DiskGeometry ()
		{
		};
	};


	class IC35L080AVVA07:public DiskGeometry	// IBM series 120GXP
	{
	 public:
		IC35L080AVVA07 ()
		{
			std::cout << "Creating IBM 120GXP IC35L080AVVA07" <<
				std::endl;

			nsurfaces = 4;
			bytes_per_sector = 512;
			cmd_ovh = 0.0002;	// in s
			seek_time = 0.0082;	// in s
			rot_latency = 0.00417;	// in s
			head_switch_time = 0.0015;	// in s
			cyl_switch_time = 0.002;	// in s
			revolution_time = 0.0083;	// in s
			interface_speed = 100000000;	// in byte/s

			int first_sect = 0;
			int last_cyl = 0;
			  add_zone (last_cyl, 1938, 928, first_sect);
			  add_zone (last_cyl, 3756, 921, first_sect);
			  add_zone (last_cyl, 5564, 896, first_sect);
			  add_zone (last_cyl, 7687, 896, first_sect);
			  add_zone (last_cyl, 9526, 888, first_sect);
			  add_zone (last_cyl, 11334, 883, first_sect);
			  add_zone (last_cyl, 13331, 864, first_sect);
			  add_zone (last_cyl, 15128, 850, first_sect);
			  add_zone (last_cyl, 16925, 840, first_sect);
			  add_zone (last_cyl, 18922, 822, first_sect);
			  add_zone (last_cyl, 20709, 806, first_sect);
			  add_zone (last_cyl, 22601, 792, first_sect);
			  add_zone (last_cyl, 24138, 787, first_sect);
			  add_zone (last_cyl, 26024, 768, first_sect);
			  add_zone (last_cyl, 27652, 752, first_sect);
			  add_zone (last_cyl, 29501, 740, first_sect);
			  add_zone (last_cyl, 31234, 725, first_sect);
			  add_zone (last_cyl, 33009, 698, first_sect);
			  add_zone (last_cyl, 34784, 691, first_sect);
			  add_zone (last_cyl, 36609, 672, first_sect);
			  add_zone (last_cyl, 38374, 648, first_sect);
			  add_zone (last_cyl, 40139, 630, first_sect);
			  add_zone (last_cyl, 41904, 614, first_sect);
			  add_zone (last_cyl, 43519, 595, first_sect);
			  add_zone (last_cyl, 45250, 576, first_sect);
			  add_zone (last_cyl, 47004, 552, first_sect);
			  add_zone (last_cyl, 48758, 533, first_sect);
			  add_zone (last_cyl, 50491, 512, first_sect);
			  add_zone (last_cyl, 52256, 493, first_sect);
			  add_zone (last_cyl, 54010, 471, first_sect);
			  add_zone (last_cyl, 55571, 448, first_sect);

			/*
			 * set<Zone,ZoneCmp>::iterator it=zones.begin();
			 * int i=0;
			 * for(;it!=zones.end();it++,i++)
			 * {
			 * //const int block_size = 128*3*1024* 4; // one cylinder
			 * 
			 * cout << "Zone " << i << " first sector: " << (*it).first_sector;
			 * cout << " sectors: " << (*it).sectors << " sustained rate: " ;
			 * cout << (*it).sustained_data_rate/1000000 << " Mb/s"  << endl;
			 * 
			 * }
			 * 
			 * 
			 * cout << "Last sector     : " << first_sect <<endl;
			 * cout << "Approx. capacity: " << (first_sect/1000000)*bytes_per_sector << " Mb" << endl;
			 */

			  std::cout << "Transfer 16 Mb from zone 0 : " <<
				get_delay (0,
					   16 * 1024 *
					   1024) << " s" << std::endl;
			  std::cout << "Transfer 16 Mb from zone 30: " <<
				get_delay (off_t (158204036) *
					   off_t (bytes_per_sector),
					   16 * 1024 *
					   1024) << " s" << std::endl;
		};
	};

	class sim_disk_request;

	//! \brief Implementation of disk emulation
	//! \remark It is emulation of IBM IC35L080AVVA07 disk's timings
	class sim_disk_file:public ufs_file_base, public IC35L080AVVA07
	{
	public:
		//! \brief constructs file object
		//! \param filename path of file
		//! \attention filename must be resided at memory disk partition
		//! \param mode open mode, see \c stxxl::file::open_modes
		//! \param disk disk(file) identifier
		sim_disk_file (const std::string & filename, int mode,int disk):ufs_file_base (filename, mode, disk)
		{
			std::cout << "Please, make sure that '" << filename <<
				"' is resided on swap memory partition!" <<
				std::endl;
		};
		request_ptr aread(void *buffer, off_t pos, size_t bytes,
			    completion_handler on_cmpl);
		request_ptr awrite(void *buffer, off_t pos, size_t bytes,
			    completion_handler on_cmpl);
		void set_size (off_t newsize);
	};

	void sim_disk_file::set_size (off_t newsize)
    {
         if (newsize > size ())
         {
             stxxl_ifcheck (::lseek (file_des, newsize - 1,
                            SEEK_SET));
             stxxl_ifcheck(::write(file_des,"",1));
         }
    };

	//! \brief Implementation of disk emulation	
	class sim_disk_request:public ufs_request_base
	{
		friend class sim_disk_file;
	protected:
		  sim_disk_request (sim_disk_file * f, void *buf, off_t off,
				    size_t b, request_type t,
				    completion_handler on_cmpl):
				ufs_request_base (f,
											 buf,
											 off,
											 b,
											 t,
											 on_cmpl)
		{
		};
		void serve ();
	public:
		const char *io_type ()
		{
			return "simdisk";
		};
  private:
    // Following methods are declared but not implemented 
    // intentionnaly to forbid their usage
		sim_disk_request(const sim_disk_request &);
    sim_disk_request & operator=(const sim_disk_request &);
		sim_disk_request();
	};

	void sim_disk_request::serve ()
	{
		//      file->set_size(offset+bytes);
		double op_start = stxxl_timestamp();
				
		void *mem =
			mmap (NULL, bytes, PROT_READ | PROT_WRITE, MAP_SHARED,file->get_file_des (), offset);
		if (mem == MAP_FAILED)
		{
			STXXL_ERRMSG( "Mapping failed." )
			STXXL_ERRMSG( "Page size: " << sysconf (_SC_PAGESIZE)
				<< " offset modulo page size" << (offset % sysconf(_SC_PAGESIZE)) )
			abort ();
		}
		else if (mem == 0)
		{
			stxxl_function_error
		}
		else
		{
			if (type == READ)
			{
				stxxl_ifcheck (memcpy (buffer, mem, bytes))
				else
				stxxl_ifcheck (munmap ((char *) mem, bytes))}
			else
			{
				stxxl_ifcheck (memcpy (mem, buffer, bytes))
				else
				stxxl_ifcheck (munmap ((char *) mem, bytes))}
			}

		double delay =
			(static_cast <sim_disk_file * >(file))->get_delay (offset, bytes);
		
		delay = delay - stxxl_timestamp() + op_start;
		
		assert( delay > 0.0 );
		
		int seconds_to_wait = static_cast < int >(floor (delay));
		if (seconds_to_wait)
			sleep (seconds_to_wait);

		usleep ((unsigned long) ((delay - seconds_to_wait) * 1000000.));

		_state.set_to (DONE);

		waiters_mutex.lock ();
		// << notification >>
		for (std::set < onoff_switch * >::iterator i =
		     waiters.begin (); i != waiters.end (); i++)
			(*i)->on ();
		waiters_mutex.unlock ();

		completed ();
		_state.set_to (READY2DIE);
	}

	request_ptr sim_disk_file::aread (void *buffer, off_t pos, size_t bytes,
				   completion_handler on_cmpl)
	{
		request_ptr req = new sim_disk_request (this, buffer, pos, bytes,
					    request::READ, on_cmpl);
		if (!req.get())
			stxxl_function_error;
		
		#ifndef NO_OVERLAPPING
		disk_queues::get_instance ()->add_readreq(req,get_id());
		#endif
    
    return req;
	};
	request_ptr sim_disk_file::awrite (
						void *buffer, off_t pos, size_t bytes,
				    completion_handler on_cmpl)
	{
		request_ptr req = new sim_disk_request (this, buffer, pos, bytes,
					    request::WRITE, on_cmpl);
    
		if (!req.get())
			stxxl_function_error;
		
		#ifndef NO_OVERLAPPING
		disk_queues::get_instance ()->add_writereq(req,get_id());
		#endif
		return req;
	};


}


#endif