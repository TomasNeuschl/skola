#pragma once

	
#include <string>
#include <vector>
namespace CDialog 
	{
		/// Shows message on screen.
		/// Function spawns centered multi-line dialog window.

		void show ( const std::vector<std::string> & message,
					const std::string & label );
	}