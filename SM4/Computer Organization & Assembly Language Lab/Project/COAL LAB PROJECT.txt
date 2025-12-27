.model small
.stack 100h

.data
    ; Menu and prompts
    welcome_msg db 0Dh, 0Ah, '=== Encrypted Note Keeper ===', 0Dh, 0Ah
                db '1. Add & Save Note', 0Dh, 0Ah
                db '2. Load & View Note', 0Dh, 0Ah
                db '3. Exit', 0Dh, 0Ah, 0Ah
                db 'Choose option (1-3): $'
    
    prompt_note db 0Dh, 0Ah, 'Enter your note (max 255 chars): $'
    prompt_key  db 0Dh, 0Ah, 'Enter 3-digit key (e.g., 123): $'
    prompt_filename db 0Dh, 0Ah, 'Enter filename (e.g., notes1.enc): $'
    prompt_loadfile db 0Dh, 0Ah, 'Enter filename to load (e.g., notes1.enc): $'
    prompt_wrong_key db 0Dh, 0Ah, 'Wrong key! Cannot decrypt.', 0Dh, 0Ah, '$'
    save_success db 0Dh, 0Ah, 'Note saved and encrypted successfully!', 0Dh, 0Ah, '$'
    file_error db 0Dh, 0Ah, 'File operation failed!', 0Dh, 0Ah, '$'
    load_success db 0Dh, 0Ah, 'Note loaded and decrypted successfully!', 0Dh, 0Ah, '$'
    invalid_key_msg db 0Dh, 0Ah, 'Invalid key format! Please enter 3 digits.', 0Dh, 0Ah, '$'
    
    ; Data buffers
    note_buffer db 255        ; Max length
                db ?         ; Actual length
                db 255 dup(?) ; Note content
                
    key_buffer db 4          ; Max 3 digits + Enter
               db ?
               db 4 dup(?)
    
    filename_buffer db 13     ; Max 12 chars (8.3 format) + null
                   db ?
                   db 13 dup(0)
    
    key dw 0                 ; Stores numeric key
    stored_key dw 0          ; Key read from file
    handle dw ?

.code
start:
    mov ax, @data
    mov ds, ax
    
menu:
    ; Clear screen
    mov ax, 0003h
    int 10h
    
    ; Display menu
    mov ah, 09h
    lea dx, welcome_msg
    int 21h
    
    ; Get user choice
    mov ah, 01h
    int 21h
    
    ; Process menu selection
    cmp al, '1'
    je add_note
    cmp al, '2'
    je view_note
    cmp al, '3'
    je exit_program
    jmp menu
    
add_note:
    ; Prompt for filename
    mov ah, 09h
    lea dx, prompt_filename
    int 21h
    
    ; Read filename
    mov ah, 0Ah
    lea dx, filename_buffer
    int 21h
    
    ; Null-terminate the filename
    mov bx, offset filename_buffer + 1
    mov cl, [bx]
    mov ch, 0
    add bx, cx
    inc bx
    mov byte ptr [bx], 0
    
    ; Prompt for note
    mov ah, 09h
    lea dx, prompt_note
    int 21h
    
    ; Read note
    mov ah, 0Ah
    lea dx, note_buffer
    int 21h
    
    ; Prompt for key
    mov ah, 09h
    lea dx, prompt_key
    int 21h
    
    ; Read key
    mov ah, 0Ah
    lea dx, key_buffer
    int 21h
    
    ; Convert key to numeric
    call convert_key_to_number
    jc invalid_key_add
    mov key, bx
    
    ; Encrypt note
    call encrypt_note
    
    ; Save to file
    call save_to_file
    jc save_failed
    
    ; Show success message
    mov ah, 09h
    lea dx, save_success
    int 21h
    
    ; Wait for key press
    mov ah, 01h
    int 21h
    
    jmp menu
    
invalid_key_add:
    mov ah, 09h
    lea dx, invalid_key_msg
    int 21h
    mov ah, 01h
    int 21h
    jmp add_note
    
save_failed:
    mov ah, 09h
    lea dx, file_error
    int 21h
    mov ah, 01h
    int 21h
    jmp menu
    
view_note:
    ; Prompt for filename
    mov ah, 09h
    lea dx, prompt_loadfile
    int 21h
    
    ; Read filename
    mov ah, 0Ah
    lea dx, filename_buffer
    int 21h
    
    ; Null-terminate the filename
    mov bx, offset filename_buffer + 1
    mov cl, [bx]
    mov ch, 0
    add bx, cx
    inc bx
    mov byte ptr [bx], 0
    
    ; Load from file
    call load_from_file
    jc load_failed
    
    ; Prompt for key
    mov ah, 09h
    lea dx, prompt_key
    int 21h
    
    ; Read key
    mov ah, 0Ah
    lea dx, key_buffer
    int 21h
    
    ; Convert key to numeric
    call convert_key_to_number
    jc wrong_key
    
    ; Compare keys
    mov ax, bx
    cmp ax, stored_key
    jne wrong_key
    
    mov key, bx
    
    ; Decrypt note
    call decrypt_note
    
    ; Show loaded message
    mov ah, 09h
    lea dx, load_success
    int 21h
    
    ; Add string terminator for display
    lea si, note_buffer + 2
    mov cl, note_buffer + 1
    mov ch, 0
    add si, cx
    mov byte ptr [si], '$'
    
    ; Display decrypted note
    mov ah, 09h
    lea dx, note_buffer + 2
    int 21h
    
    ; Wait for key press
    mov ah, 01h
    int 21h
    
    jmp menu
    
load_failed:
    mov ah, 09h
    lea dx, file_error
    int 21h
    mov ah, 01h
    int 21h
    jmp menu
    
wrong_key:
    mov ah, 09h
    lea dx, prompt_wrong_key
    int 21h
    mov ah, 01h
    int 21h
    jmp view_note
    
exit_program:
    mov ah, 4Ch
    int 21h

; =============================================
; Procedures
; =============================================

convert_key_to_number proc near
    ; Input: key_buffer with digits
    ; Output: BX = numeric key, CF=1 if invalid
    mov si, offset key_buffer + 2
    mov cl, key_buffer + 1
    mov ch, 0
    mov bx, 0
    
    ; Check if we have at least 1 digit
    cmp cx, 0
    je invalid_digit
    
convert_loop:
    cmp cx, 0
    je convert_done
    
    mov al, [si]
    ; Skip carriage return (13) and line feed (10)
    cmp al, 13
    je skip_char
    cmp al, 10
    je skip_char
    
    sub al, '0'
    cmp al, 0
    jl invalid_digit
    cmp al, 9
    jg invalid_digit
    
    ; BX = BX * 10 + digit
    push ax
    mov ax, bx
    mov dx, 10
    mul dx
    mov bx, ax
    pop ax
    add bl, al
    adc bh, 0
    
skip_char:
    inc si
    dec cx
    jmp convert_loop
    
invalid_digit:
    stc
    ret
    
convert_done:
    clc
    ret
convert_key_to_number endp

encrypt_note proc near
    ; Encrypts note using XOR with key
    lea si, note_buffer + 2
    mov cl, note_buffer + 1
    mov ch, 0
    mov bx, key
    
encrypt_loop:
    cmp cx, 0
    je encrypt_done
    xor [si], bl
    inc si
    dec cx
    jmp encrypt_loop
    
encrypt_done:
    ret
encrypt_note endp

decrypt_note proc near
    ; Decrypts note using XOR with key (same as encrypt for XOR)
    lea si, note_buffer + 2
    mov cl, note_buffer + 1
    mov ch, 0
    mov bx, key
    
decrypt_loop:
    cmp cx, 0
    je decrypt_done
    xor [si], bl
    inc si
    dec cx
    jmp decrypt_loop
    
decrypt_done:
    ret
decrypt_note endp

save_to_file proc near
    ; Creates/overwrites file and saves encrypted note
    ; Input: filename_buffer contains filename
    ;        note_buffer contains encrypted data
    ;        key contains encryption key
    ; Output: CF=1 if error
    
    ; Create file
    mov ah, 3Ch
    mov cx, 0              ; Normal attributes
    lea dx, filename_buffer + 2
    int 21h
    jc save_error
    
    mov handle, ax
    
    ; Write key first
    mov ah, 40h
    mov bx, handle
    mov cx, 2
    lea dx, key
    int 21h
    jc save_error_close
    
    ; Write note length
    mov ah, 40h
    mov bx, handle
    mov cx, 1
    lea dx, note_buffer + 1
    int 21h
    jc save_error_close
    
    ; Write encrypted note content
    mov ah, 40h
    mov bx, handle
    mov cl, note_buffer + 1
    mov ch, 0
    lea dx, note_buffer + 2
    int 21h
    jc save_error_close
    
    ; Close file
    mov ah, 3Eh
    mov bx, handle
    int 21h
    jc save_error
    
    clc
    ret
    
save_error_close:
    ; Close file before returning error
    mov ah, 3Eh
    mov bx, handle
    int 21h
    
save_error:
    stc
    ret
save_to_file endp

load_from_file proc near
    ; Loads encrypted note from file
    ; Input: filename_buffer contains filename
    ; Output: CF=1 if error
    
    ; Open file
    mov ah, 3Dh
    mov al, 0              ; Read-only
    lea dx, filename_buffer + 2
    int 21h
    jc load_error
    
    mov handle, ax
    
    ; Read key first
    mov ah, 3Fh
    mov bx, handle
    mov cx, 2
    lea dx, stored_key
    int 21h
    jc load_error_close
    cmp ax, cx
    jne load_error_close
    
    ; Read note length
    mov ah, 3Fh
    mov bx, handle
    mov cx, 1
    lea dx, note_buffer + 1
    int 21h
    jc load_error_close
    cmp ax, cx
    jne load_error_close
    
    ; Read encrypted note content
    mov ah, 3Fh
    mov bx, handle
    mov cl, note_buffer + 1
    mov ch, 0
    lea dx, note_buffer + 2
    int 21h
    jc load_error_close
    cmp ax, cx
    jne load_error_close
    
    ; Close file
    mov ah, 3Eh
    mov bx, handle
    int 21h
    jc load_error
    
    clc
    ret
    
load_error_close:
    ; Close file before returning error
    mov ah, 3Eh
    mov bx, handle
    int 21h
    
load_error:
    stc
    ret
load_from_file endp

end start