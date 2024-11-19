COMMENT @
	Copyright 2025-9999 sub1to

	This file is part of CTNinja

	CTNinja is free software; See LICENSE.txt or https://opensource.org/license/mit
@

.CODE

	PUBLIC _get_teb

	_get_teb PROC

		mov rax, gs:[30h]
		ret

	_get_teb ENDP

END

